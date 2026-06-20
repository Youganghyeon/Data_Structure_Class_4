A = {
    0: [1, 2, 3],
    1: [0, 2, 4, 5],
    2: [0, 1, 6],
    3: [0],
    4: [1],
    5: [1],
    6: [2]
}

def bfs(A):
    """
    리스트를 큐처럼 사용하여 BFS를 구현했습니다.

    BFS는 너비 우선 탐색이므로 시작 노드와 가까운 노드부터 차례대로 방문합니다.
    시작 노드는 0입니다.

    queue는 앞으로 방문할 노드를 저장하는 리스트입니다.
    append()를 사용하여 노드를 뒤에 추가하고,
    pop(0)을 사용하여 앞에 있는 노드를 꺼냅니다.
    따라서 FIFO, 큐의 구조가 됩니다.

    1. 시작 노드를 queue와 isVisited에 넣습니다.
    2. queue에서 가장 앞에 있는 노드를 꺼내 방문합니다.
    3. 현재 노드와 연결된 인접 노드를 확인합니다.
    4. 아직 방문하지 않은 노드라면 isVisited에 넣고 queue에도 추가합니다.
    5. queue가 빌 때까지 위 과정을 반복합니다.

    :param A  : 그래프를 표현한 인접 리스트 딕셔너리
    :return   : BFS 순서대로 방문한 노드 리스트
    """
    answer = []
    # TODO : BFS로 탐색하는 로직을 구현해주세요.
    # 방문한 노드를 순서대로 answer 리스트에 넣어서 리턴해주세요.
    isVisited = []
    queue = []
    top_node = list(A.keys())[0]
    queue.append(top_node)
    isVisited.append(top_node)

    while queue:
        current_node = queue.pop(0)
        answer.append(current_node)

        for neighbor in A[current_node]:
            if neighbor not in isVisited:
                isVisited.append(neighbor)
                queue.append(neighbor)

    return answer


def dfs(A):
    """
    재귀를 통한 DFS 구현입니다.
    같은 레벨의 노드가 여러 개라면 더 작은 번호의 노드부터 방문해야 합니다.

    시작 노드는 0입니다.
    0과 연결된 1, 2, 3은 같은 레벨의 노드입니다.
    4, 5, 6은 그보다 더 깊은 레벨의 노드입니다.

    DFS는 깊이 우선 탐색이므로 현재 노드에서 더 깊이 내려갈 수 있는 노드를 먼저 방문합니다.
    따라서 인접 노드를 확인할 때,
    1. 시작 노드의 인접 노드에 포함되는 노드는 같은 레벨 노드 리스트(same_level)에 넣고,
    2. 그 외의 노드는 더 깊은 레벨의 노드 리스트(lower_level)에 넣습니다.
    3. lower_level을 먼저 재귀 호출한 뒤 same_level을 재귀 호출합니다.
    4. A의 각 인접 리스트는 오름차순으로 정렬되어 있으므로 같은 레벨 안에서는 작은 번호부터 방문됩니다.

    :param A  : 그래프를 표현한 인접 리스트 딕셔너리
    :return   : DFS 순서대로 방문한 노드 리스트

    """
    answer = []
    # TODO : DFS로 탐색하는 로직을 구현해주세요.
    # 방문한 노드를 순서대로 answer 리스트에 넣어서 리턴해주세요.
    isVisited = []

    top_node = list(A.keys())[0]
    top_neighbors = A[top_node]
    def recur_dfs(node):
        """
        현재 노드를 방문하고, 인접 노드를 lower_level과 same_level로 나누어 재귀 탐색합니다.
        """
        isVisited.append(node)
        answer.append(node)

        lower_level = []
        same_level = []

        for neighbor in A[node]:
            if neighbor not in isVisited:
                if neighbor in top_neighbors:
                    same_level.append(neighbor)
                else:
                    lower_level.append(neighbor)

        for neighbor in lower_level:
            if neighbor not in isVisited:
                recur_dfs(neighbor)

        for neighbor in same_level:
            if neighbor not in isVisited:
                recur_dfs(neighbor)

    recur_dfs(top_node)
    return answer
# 아래는 체크함수입니다. 수정하실 필요 없습니다.
bfs_result = bfs(A)
dfs_result = dfs(A)

assert bfs_result == [0,1,2,3,4,5,6]
assert dfs_result == [0,1,4,5,2,6,3]
print('PASSED!')

