#include <string>
#include <vector>
#include <iostream>

using namespace std;

int maxNum = 0;

int searchMax(vector<int>& tree, vector<bool>& visited, const int pos, int d)
{
    if (pos >= tree.size())
    {
        return 0;
    }
    else if (visited[pos])
    {
        return tree[pos];
    }

    visited[pos] = true;
    int left = pos + d;
    int right = pos + d + 1;

    int lm = searchMax(tree, visited, left, d + 1);
    int rm = searchMax(tree, visited, right, d + 1);

    int max = lm > rm ? lm : rm;

    tree[pos] += max;

    return tree[pos];
}

int solution(vector<vector<int>> triangle) {
    int answer = 0;
    vector<int> tree;
    vector<bool> visited;

    for (vector<int>& items : triangle)
    {
        for (int item : items)
        {
            tree.push_back(item);
            visited.push_back(false);
        }
    }


    searchMax(tree, visited, 0, 1);
    return tree[0];
}

int main()
{
    bool a = 5;
    long long n = reinterpret_cast<long long>(&a);

    solution({ {7}, {3, 8} });
}   

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
