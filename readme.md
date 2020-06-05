
# shear.cpp
## rowsort, rowrevsort, colsort, shear_sort_thread, shear_sort
멀티 스레드 환경에서 2차원 어레이를 읽고 각 스레드에서 따로 어레이를 분류합니다.
상호배제 원칙을 준수하여 각 스레드가 각자의 일을 하면서도 의도된 결과를 도출하도록 테스트하는 코드입니다.
테스트 결과 스레드가 어느 순서로 실행되든지 같은 결과를 프린트 했습니다.

### rowsort, rowrevsort, colsort
	-3가지 방향으로 분리된 재배열 알고리즘을 각자 실행합니다.

### shear_sort_thread
	-모든 스레드가 한단계씩 같은 속도로 진행하기 위해 대기합니다.

### shear_sort
	-스레드를 만들고 종료시킵니다.
