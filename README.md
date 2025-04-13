## pipex  
Linux 쉘에서 주로 사용되는 명령어 파이프라인을 구현하는 과제입니다.  
 
### 목차
- [1. 구현 세부 사항](#1-구현-세부-사항)
- [2. 주요 기술적 이슈와 해결 과정](#2-주요-기술적-이슈와-해결-과정)
- [3. 평가 피드백](#3-평가-피드백)

### 1. 구현 세부 사항
#### 필수 과제  
예를 들어 아래와 같이 인자가 들어왔을 때:  
~~~
./pipex file1 cmd1 cmd2 file2
~~~
이 shell command와 정확하게 동일한 행동을 해야 합니다:  
~~~
$> < file1 cmd1 | cmd2 > file2
~~~
#### 추가 과제  
1. **Handling multiple pipes.**
인자가 아래와 같이 들어왔을 때:
```
$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```
이 shell command와 정확하게 동일한 행동을 해야 합니다:
```
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
```
2. **첫 번째 파라미터가 "here_doc"일 때 << 그리고 >> 커맨드를 지원해야 한다.**  
인자가 아래와 같이 들어왔을 때:
```
$> ./pipex here_doc LIMITER cmd cmd1 file
```
이 shell command와 정확하게 동일한 행동을 해야 합니다:
~~~
cmd << LIMITER | cmd1 >> file
~~~

### 2. 주요 기술적 이슈와 해결 과정  
#### 2-1) 프로세스 생성을 어떤 방식으로 할 것인가?
프로젝트 진행 중 마주친 주요 문제점은 **프로세스 관리 구조**였습니다. 자식 프로세스가 다시 새로운 자식 프로세스를 생성하는 다중 계층 구조를 채택하여 진행하였는데 이는 다음과 같은 문제를 야기했습니다:  

- 인자로 들어온 cmd의 실행을 위해서는 자식 프로세스에서 execve 시스템 콜의 실행이 필수적
- 하지만, 자식 프로세스에서 execve 시스템 콜 실행 시 손자의 pid 정보를 상실하는 문제 발생
- 즉, 손자 프로세스는 고아 프로세스가 됨
- 이대로 진행한다면 고아 프로세스를 양산하는 프로그램이 되어버림

따라서 자식 프로세스가 자식 프로세스를 생성하는 다중 계층 구조 대신 부모 프로세스가 모든 자식 프로세스를 생성하는 중앙 집중 구조를 채택하여 고아 프로세스의 발생 가능성을 차단했습니다.  
이 경험을 통해 근본적으로 잘못된 구조는 필연적으로 문제를 발생시킨다는 것을 깨달을 수 있었고 로직 설계 시 다양한 관점에서 문제 발생 가능성을 고려하는 습관의 초석을 다질 수 있었습니다.

#### 2-2) 파이프의 병렬 동작을 어떻게 구현할 것인가?
파이프 연산자는 병렬적으로 동작합니다. 예를 들어 `sleep 1 | sleep 1 | sleep 1`과 같은 커맨드는 실행하는 데 3초가 아닌 1초가 걸려야 합니다. 이 문제의 경우 처음에는 구현조차 할 수 없었는데 그 이유는 파이프의 병렬 동작에 대한 제 오해 때문이었습니다. 저는 "같은 출발선에서 무조건 동시에 출발하여 무조건 동시에 결승선에 골인"을 의미한다고 오해하고 있었는데 실제로는 "같은 출발선에서 동시에 출발"만을 의미한다는 것을 동료 학습을 통해 알게 되었습니다. 그 후 입력이 필요한 커맨드들은 자체적으로 입력이 들어올 때까지 출발선에서 대기하다가 입력이 들어오면 그때 또 진행됩니다.

이렇게 병렬 동작을 이해하고 난 후 실제 코드는 아래와 같이 구현했습니다:
~~~
#include "../pipex.h"
void	transfer_data_to_file2(t_parsing *parsing, t_process *process, \
char **envp)
{
	process->i = -1;
	while (++process->i < parsing->cmd_cnt)
	{
		if (pipe(process->pipe_fd) == -1)  //pipe 생성
		{
			perror("failed opening pipe\n");
			exit(1);
		}
		process->pid = fork();  
		if (process->pid == 0)  //자식 프로세스는 여기로 진행
			first_or_middle_or_last_child(parsing, process, envp);
		else  //부모 프로세스는 여기로 진행
			parent(parsing, process);
	}
}
~~~

#### 2-3) 파이프는 정말 병렬적으로 동작하는가?
위와 같이 코드를 짜고 나서 보니 의문이 생겼습니다.  
제 코드는 while문 안에서 fork를 한 뒤 first_or_middle_or_last_child 함수에서 execve 시스템 콜을 호출합니다. 그런데 `sleep 1 | sleep 1 | sleep 1`이라는 커맨드가 입력으로 들어왔을 때 2번째 sleep 커맨드는 첫 번째 sleep 커맨드보다 논리적으로 나중에 실행될 수밖에 없습니다. 그렇다면 이 코드는 파이프의 병렬 동작을 실제로 구현한 것이 아니라고 볼 수 있지 않냐는 의문이 들었습니다.  

그 해답은 컴퓨터 구조에서 찾을 수 있었습니다. 결론부터 말하자면 논리적으로도 완벽하게 병렬로 실행되도록 구현하는 것은 불가능합니다.  
그 이유는 아래와 같습니다.  

##### *2-3-1) cpu는 한 번에 하나의 명령만 실행할 수 있다.*  
sleep이 실행되려면 간단히 말해 (fork -> execve) 시스템 콜의 과정을 거칩니다. 즉, `sleep 1 | sleep 1 | sleep 1` 커맨드는 cpu가 한 번에 하나의 명령만을 실행할 수 있기 때문에 (fork -> execve) -> (fork -> execve) -> (fork -> execve)처럼 순차적으로 실행될 수밖에 없습니다.  

##### *2-3-2) cpu의 명령어 파이프라이닝(Instruction-Level Parallelism)을 이용할 수는 없을까?*  
일단 이 맥락에서의 명령어는 하나의 프로그램도 아닐 뿐더러 cpu 파이프라이닝도 명령어 인출, 해석, 실행, 결과 저장의 4단계를 서로 겹치지 않게 번갈아가며 실행하므로 엄밀한 의미에서의 병렬성이라고 볼 수는 없습니다. 즉, 애초에 명령어의 개념 자체가 다르고 진정한 의미의 병렬성도 아닙니다.

##### *2-3-3) 멀티코어 cpu라면 가능하지 않을까?*  
이 역시 불가능합니다. 멀티코어 cpu라고 하더라도 결국 명령의 실행 순서는 cpu scheduler가 관장하기 때문에 소스코드 레벨에서 이 특성을 이용하는 것은 불가능합니다.

결론적으로 파이프의 병렬 동작은 소스코드 레벨에서는 컴퓨터의 동시성을 이용해서 병렬적으로 동작되는 "것처럼" 보이게 하는 것이 진정한 의미라고 볼 수 있다는 결론을 내렸고 위의 구현을 유지한 채로 프로젝트를 마무리하였습니다.
이 프로젝트를 진행하며 처음에는 막연히 병렬적 동작이라는 용어와 제 프로그램의 실제 구조가 아무리 생각해도 달라서 너무나 혼란스러웠지만 실제 구현과 하드웨어 아키텍쳐를 면밀히 비교하면서 결국 정확한 의미를 짚어낼 수 있었습니다.  
만약 이 과제를 통해 직접 몸으로 부딪쳐보지 않았더라면 병렬성과 동시성에 대하여 이토록 현실적이고 깊이있게 생각해보지는 못했을 것입니다. 단순 지식 암기 또한 기초를 쌓는 과정에서 무시할 수 없는 부분이지만 그보다 더 중요한 것은 실제 현장에서 몸으로 부딪쳐보며 스스로를 끊임없이 의심하는 태도라는 걸 배울 수 있었습니다.

 
### 3. 평가 피드백  
<img width="639" alt="스크린샷 2024-12-29 오후 4 07 42" src="https://github.com/user-attachments/assets/f0b19978-a04b-4049-a5a4-75c4cfded1c7" />
