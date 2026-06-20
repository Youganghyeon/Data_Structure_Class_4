import sys

## 입력 받는 코드입니다. 수정할 필요 없습니다.
sys.stdin = open('case.txt')
N, M = list(map(int,input().split()))
print(N, M)
concerts = []
for v in range(N):
    values = list(map(int, input().split()))
    concerts.append(values)
# print(concerts)
# [[1, 0, 0, 1, 1, 0], [1, 0, 1, 1, 0, 0], [1, 1, 1, 1, 0, 1], [0, 1, 1, 0, 1, 1], [0, 1, 0, 0, 1, 0]]
###################################

def count_stages(concerts):
    """
    콘서트장에서 펜스로 나누어진 독립 무대공간의 개수를 계산합니다.
    1은 펜스이고, 0은 무대공간입니다.

    상하좌우로 연결된 0은 독립 무대공간입니다.
    콘서트장 전체를 한 칸씩 확인하다가 아직 방문하지 않은 0을 만나면
    새로운 무대공간을 하나 발견한 것이라고 판단할 수 있습니다.

    새로운 무대공간을 발견하면 DFS로 그 위치와 연결된 모든 0을 찾습니다.
    찾은 0은 1로 바꿔 방문 처리합니다.
    이렇게 하면 같은 무대공간을 중복해서 세지 않을 수 있습니다.
    """
    answer = 0
    # TODO : 콘서트 공간에서 무대의 개수를 계산해 반환해주는 함수를 작성해주세요.
    N = len(concerts)
    M = len(concerts[0])

    def dfs(r, c):
        """
        현재 위치가 콘서트장 범위를 벗어나면 탐색을 멈춥니다.

        현재 위치에서 시작해 상하좌우로 연결된 노드를 모두 확인합니다.
        
        현재 위치가 0이 아니라면 펜스이거나 이미 확인한 노드이므로 멈춥니다.
        현재 위치가 0이면 아직 확인하지 않은 노드입니다.

        이 칸을 1로 바꿔 다시 방문하지 않도록 표시합니다.
        그 다음 위, 아래, 왼쪽, 오른쪽 칸을 같은 방식으로 탐색합니다.
        """

        if r < 0 or r >= N or c < 0 or c >= M:
            return

        if concerts[r][c] != 0:
            return

        concerts[r][c] = 1

        dfs(r - 1, c)
        dfs(r + 1, c)
        dfs(r, c - 1)
        dfs(r, c + 1)

    for r in range(N):
        for c in range(M):
            if concerts[r][c] == 0:
                answer += 1
                dfs(r, c)

    return answer

print(count_stages(concerts))
