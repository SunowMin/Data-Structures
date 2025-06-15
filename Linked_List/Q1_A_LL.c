//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{    // 단일 노드를 표현하는 구조체
	int item;                // 실제 데이터 (정수 하나)
	struct _listnode *next;  // 다음 노드의 주소
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{  // 전체 연결 리스트를 대표하는 구조체
	int size;                // 현재 노드의 개수
	ListNode *head;          // 첫 번째 노드의 주소
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;   // 연결리스트 변수 선언
	int c, i, j;     // 메뉴 선택(c), 입력값(i), 삽입 결과 인덱스(j)
	c = 1;           // while문 진입을 위해 c에 1로 초기화

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;  // 리스트의 시작 노드가 없음을 의미
	ll.size = 0;	 // 리스트에 노드가 없으므로 크기 0으로 설정

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			// removeAllItems(&ll);  -> 해당 구문 있으면 노드 삭제됨
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
// 조건
// 1. 정렬된 연결 리스트에 오름차순으로 입력받은 정수를 삽입
// 2. 이미 존재하는 값이면 삽입하지 않고 -1 반환
// 3. 삽입이 성공하면 새 값이 들어간 인덱스를 반환

// 입력 : 2, 3, 5, 7, 9 리스트에 8 입력
// 결과 : 2, 3, 5, 7, 8, 9
int insertSortedLL(LinkedList *ll, int item)
{
	// 리스트 포인터 자체가 NULL이면 함수 종료
	if(ll == NULL){
		return -1;
	}

	ListNode *cur = ll->head;             // cur을 리스트의 head로 초기화
	int index = 0;						  // 삽입할 위치를 저장할 인덱스 변수

	// 리스트 앞에서부터 순회하면서 삽입 위치를 찾음
	while(cur != NULL){
	// 현재 노드의 값이 item과 같으면 
		if(item == cur->item)
			return -1; 	// 중복이므로 -1 반환
	// 현재 노드의 값이 item보다 크면 break (삽입위치를 찾음!)
		if(item < cur->item){
			break;
		}

		cur = cur->next;		// 다음 노드로 이동
		index++;				// 인덱스 증가
	}

	// 찾은 인덱스 위치에 새로운 item 삽입
	// insertNode는 삽입 성공 시 0 반환
	if(insertNode(ll, index, item) == 0){
		return index;			// 삽입 성공 -> 삽입된 위치의 인덱스 반환
	}
	else{
		return -1;				// 삽입 실패
	}
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;   // 포인터 cur 선언 - 리스트를 순회하며 각 노드를 가리키는 데 사용
	if (ll == NULL)  // 리스트 포인터 ll이 NULL이면 함수 종료 -> 연결리스트 자체가 아예 전달되지 않은 경우
		return;      
	cur = ll->head;                // cur을 리스트의 시작노드에 저장

	if (cur == NULL)               // 리스트가 비어 있는 경우
		printf("Empty");
	while (cur != NULL)            // 노드가 존재하는 동안 계속 순회
	{
		printf("%d ", cur->item);  // 현재 노드의 데이터를 출력하고
		cur = cur->next;           // 다음 노드를 가리키도록 cur을 이동
	}
	printf("\n");
}

// 리스트에 있는 모든 노드를 제거(메모리 해제)
void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;     // 리스트의 시작점인 head를 가리키는 포인터 선언
	ListNode *tmp;                // cur이 가리키는 노드를 free()한 뒤에도 다음 노드를 기억해야 하므로 필요

	while (cur != NULL){
		tmp = cur->next;          // 현재 노드의 다음 노드를 tmp에 저장
		free(cur);                // 현재 노드에 할당된 메모리를 해제
		cur = tmp;                // cur을 한 칸 앞으로 이동
	}
	ll->head = NULL;              // 모든 노드를 제거한 후, 리스트를 빈 상태로 초기화
	ll->size = 0;
}

// 연결리스트에서 특정 인덱스에 있는 노드를 찾아 반환하는 함수
ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;   // 노드를 순차적으로 따라가기 위한 포인터 temp 선언

	// 연결 리스트가 존재하지 않거나, 인덱스가 음수이거나, 인덱스가 리스트 범위를 초과하면 NULL 반환
	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;   // 리스트의 첫 번째 노드 주소를 temp에 저장

	if (temp == NULL || index < 0)   // 리스트가 비어 있거나, 인덱스가 음수일 경우
		return NULL;

	while (index > 0){
		temp = temp->next; // temp를 다음 노드로 이동시키며 index를 줄여나감
		if (temp == NULL)  // NULL을 만나면(=잘못된 구조거나 끝을 넘음) NULL 반환
			return NULL;
		index--;
	}

	return temp;
}

// 특정 인덱스 위치(index)에 노드(value)를 삽입하는 함수
int insertNode(LinkedList *ll, int index, int value){

	// pre:삽입 위치 바로 앞 노드, cur:삽입 위치 현재 노드 또는 기존의 head
	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	// (목록이 비어 있거나 첫 번째 노드를 삽입하는 경우 헤드 포인터를 업데이트해야 합니다.)
	if (ll->head == NULL || index == 0){
		cur = ll->head;                     // 현재의 head를 cur에 잠깐 저장
		ll->head = malloc(sizeof(ListNode));// 새 노드를 동적으로 생성해서 head에 바로 연결해서 맨 앞에 배치
		ll->head->item = value;             // value 저장
		ll->head->next = cur;				// 기존의 첫번째 노드를 새 노드의 next로 연결
		ll->size++;							// 노드 하나가 추가되었으니 리스트 크기를 1 증가
		return 0;
	}

	// Find the nodes before and at the target position (목표 위치 앞과 그 위치에 있는 노드를 찾습니다.)
	// Create a new node and reconnect the links (새 노드를 생성하고 링크를 다시 연결합니다.)
	// index-1 위치의 노드를 찾아서 pre 포인터에 저장
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;                        // pre다음에 있었던 기존 노드를 cur에 저장
		pre->next = malloc(sizeof(ListNode));   // 새로운 노드를 동적할당해서 pre뒤에 끼워 넣음
		pre->next->item = value;				// 새로운 노드에 value 저장
		pre->next->next = cur;					// 새로 만든 노드의 next 포인터를 cur가 가리키고 있던 노드로 연결
		ll->size++;								// 노드 하나가 추가되었으니 리스트 크기를 1 증가
		return 0;
	}

	return -1;
}

// 연결 리스트에 지정된 인덱스의 노드를 삭제하는 함수
int removeNode(LinkedList *ll, int index){
	// 구조체 listnode 타입의 pre, cur 포인터 변수 선언
	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	// 예외처리1. 리스트가 없거나, 인덱스가 0보다 작거나, 인덱스가 리스트 크기 이상이면
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	// 예외처리2. 첫 번째 노드를 삭제하는 경우 (head 노드 삭제)
	if (index == 0){
		cur = ll->head->next;      // 두 번째 노드를 저장
		free(ll->head);			   // 첫 번째 노드를 메모리에서 해제
		ll->head = cur;            // head를 두 번째 노드로 바꿈
		ll->size--;				   // 사이즈 감소

		return 0;
	}

	// Find the nodes before and after the target position (목표 위치의 앞뒤 노드를 찾습니다.)
	// Free the target node and reconnect the links (목표 노드를 해제하고 링크를 다시 연결합니다.)
	if ((pre = findNode(ll, index - 1)) != NULL){

		// pre가 마지막 노드라면 NULL이므로 삭제할 노드 없음
		if (pre->next == NULL)
			return -1;

		cur = pre->next;        // 삭제할 노드를 cur에 저장
		pre->next = cur->next;  // cur를 건너뛰고 cur 다음 노드와 연결
		free(cur);				// cur을 메모리에서 해제
		ll->size--;				// 리스트 크기 감소
		return 0;
	}

	return -1;
}
