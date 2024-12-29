
## pipex  
Linux 쉘에서 주로 사용되는 명령어 파이프라인을 구현하는 과제입니다.  
예를 들어 아래와 같이 인자가 들어왔을 때:  
~~~
./pipex file1 cmd1 cmd2 file2
~~~

이 shell command와 정확하게 동일한 행동을 해야 합니다:  
~~~
$> < file1 cmd1 | cmd2 > file2
~~~


목차
  1. 어려웠거나 아쉬웠던 점
  2. 평가 피드백
  3. 프로젝트 개요

### 1. 어려웠거나 아쉬웠던 점  
  1-1) 고아 프로세스를 양산하는 설계
   - 처음에는 자식이 자식을 fork하고 자식의 자식이 또 다시 fork하는 식의 설계대로 진행했습니다.
   - 그러나 이렇게 되면 모든 자식 프로세스들은 자식의 자식 프로세스의 부모 프로세스가 됩니다.
   - 이렇게 되면 시조 부모를 제외한 모든 프로세스에서 execve를 실행했을 때 모든 자식 프로세스의 pid 정보는 사라지게 됩니다.
   - 즉, 모든 자식 프로세스가 고아 프로세스가 되는 것입니다.
   - 방향 자체가 잘못된 설계로 인해 부모 프로세스만이 fork를 관리하는 식으로 전체 방향을 재수정해야 했습니다.

### 2. 평가 피드백  
<img width="639" alt="스크린샷 2024-12-29 오후 4 07 42" src="https://github.com/user-attachments/assets/f0b19978-a04b-4049-a5a4-75c4cfded1c7" />

### 3. 프로젝트 개요  
