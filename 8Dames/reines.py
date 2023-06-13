def search(board, n, ligne):
    for i in range(0,n):
        for j in range(n):
            if(isSafe(board, i, j)):
                for x in range(n):
                    board[x][j] = 2
                    board[i][x] = 2
                    if(i+x < n and j+x < n):
                        board[i+x][j+x] = 2
                    if(i-x >= 0 and j-x >= 0):
                        board[i-x][j-x] = 2
                    if(i+x < n and j-x >= 0):
                        board[i+x][j-x] = 2
                    if(i-x >= 0 and j+x < n):
                        board[i-x][j+x] = 2
                    
                board[i][j] = 1
                search(board, n, ligne+1)
                board[i][j] = 0

def isSafe(board, i , j):
    return True

board = [[0 for x in range(8)] for y in range(8)]
search(board, 8,0)