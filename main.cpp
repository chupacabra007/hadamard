#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <ctime>
#include <algorithm>

using uchar = unsigned char;
using ushort = unsigned short int;


class Hadamard {
  
public:

    Hadamard(uchar K): K(K), ORDER(4 * K) { 
        matrix = new int *[ORDER];    
    }
 
 
    void find()
    {
        while(true) {
            int **fmt = new int *[K];
            setDiagonalMatrix(fmt, K * 4);            
            
            int **omt = new int *[4];            
            setOnesMatrix(omt);
            
            int ***blocks = new int **[4];
            int ***blocks_init = new int **[4];
            setHadamardBlocks(omt, blocks, blocks_init);
            
            bool found = findHadamardBlocks(blocks, blocks_init, fmt);   
            
            if (found) {
                buildHadamardMatrix(blocks_init);
                printHadamardMatrix();
                break;      
            }
        } 	  
    }    
    
    
private:
    const uchar K;
    const ushort ORDER;
    int ***hadamard_blocks = new int **[4];
    int **matrix;
    
    template <typename T>
    void setOnesMatrix(T **arr)
    {
        for (uchar i = 0; i < 4; ++i)
        {
            arr[i] = new T[K];
            setOnesRow(arr[i]);    	  
        }
    }
    
    
    template <typename T>
    void setOnesRow(T *row)
    {
        const uchar num_of_negatives = numOfNegatives();
        std::vector<uchar> indices;
        
        for (uchar i = 0; i < K; ++i)
        {
            row[i] = 1;
            if (i > 0) 
            {
                indices.push_back(i);
            }
        }
        std::random_shuffle(indices.begin(), indices.end());
        
        for (uchar i = 0; i < num_of_negatives; ++i)
        {
            row[indices.at(i)] = -1;    
        }
        
    }
    
    template <typename T>
    void printOnesRow(T *row)
    {
        for (uchar i = 0; i < K; ++i)
        {
            std::cout << row[i] << " ";      
        }
        std::cout << std::endl;  
    }
    
    
    const uchar numOfNegatives()
    {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<uchar> uni(0, K - 1);
        return uni(rng);
    }
    
    
    template <typename T, typename T2>
    void setZeroMatrix(T **arr, T2 rows, T2 cols)
    {
        for (T2 i = 0; i < rows; ++i)
        {
            arr[i] = new T[cols];
            for (T2 j = 0; j < cols; ++j)
            {
                arr[i][j] = 0;            
            } 
        }
    }
    
    
    template <typename T>
    void setIdentityMatrix(T **arr)
    {
        for (uchar i = 0; i < K; ++i)
        {
            arr[i] = new T[K];
            for (uchar j = 0; j < K; ++j)
            {
                arr[i][j] = 0;            
            }
            arr[i][i] = 1;  
        }
    }
    
    
    template <typename T>
    void shiftIdentityMatrix(T **arr)
    {
        bool one;
    	bool hit;
    	for (uchar i = 0; i < K; ++i)
    	{
    	    one = false;
    	    hit = false;
    	    for (uchar j = 0; j < K; ++j)
            {
                if (j == 0 && arr[i][K-1] == 1)
                {
                    arr[i][0] = 1;
                    continue;            	  
                }
            	  
            	if (!hit && arr[i][j] == 1)
            	{
                    arr[i][j] = 0;
                    one = true;
                    continue;            	  
            	}
            	  
            	if (one)
            	{
                    arr[i][j] = 1;
                    one = false;
                    hit = true;            	  
            	} else {
                    arr[i][j] = 0;            	  
                }
            }        
        }
    }
    
    
    template <typename T>
    void printMatrix(T **arr, ushort rows, ushort cols)
    {
        for (ushort i = 0; i < rows; ++i)
        {
            for (ushort j = 0; j < cols; ++j)
            {
                std::cout << arr[i][j] << " ";
            }
            std::cout << std::endl;
        } 
        std::cout << std::endl;   
    }
    
    
    template <typename T>
    void sumMatrices(T **lmt, T **rmt)
    {
        for (uchar i = 0; i < K; ++i)
        {
            for (uchar j = 0; j < K; ++j)
            {
                lmt[i][j] = lmt[i][j] + rmt[i][j];           
            }       
        }    
    }
    
    template <typename T>
    void setDiagonalMatrix(T **arr, const T val)
    {
        for (ushort i = 0; i < K; ++i)
        {
            arr[i] = new T[K];
            for (ushort j = 0; j < K; ++j)
            {
                arr[i][j] = (i == j) ? val : 0;         
            }
        } 
    }
    
    
    template <typename T>
    void squareMatrix(T **arr)
    {
        T val = 0;
        T **acc = new T *[K];
        
        for (uchar i = 0; i < K; ++i)
        {
            acc[i] = new T[K];
            for (uchar j = 0; j < K; ++j)
            {
                val = 0;
                for (uchar k = 0; k < K; ++k) 
                {
                    val += arr[i][k] * arr[k][j];                    
                }
                acc[i][j] = val;          
            }
        }
        
        for (uchar i = 0; i < K; ++i)
        {
            for (uchar j = 0; j < K; ++j)
            {
                arr[i][j] = acc[i][j];            
            }        
        }
    }
    
    
    template <typename T>
    bool matricesAreEqual(T **lmt, T **rmt)
    {
        for (uchar i = 0; i < K; ++i)
        {
            for (uchar j = 0; j < K; ++j)
            {
                if (lmt[i][j] != rmt[i][j])
                    return false;            
            }        
        }        
        return true;
    }
    
    
    template <typename T>
    void setHadamardBlocks(T **ones, T ***blocks, T ***blocks_init)
    {
        for (uchar i = 0; i < 4; ++i)
        {
            blocks[i] = new T *[K];
            blocks_init[i] = new T *[K]; 
            setHadamardBlock(i, ones[i], blocks[i], blocks_init);       
        }
    }
    
    
    template <typename T>
    void setHadamardBlock(uchar idx, T *ones, T **block, T ***blocks_init)
    {
         setZeroMatrix(block, K, K);
         
         T **imt = new T *[K];
         setIdentityMatrix(imt);
         
         for (uchar i = 0; i < K; ++i)
         {
             for (uchar j = 0; j < K; ++j)
             {
                 for (uchar k = 0; k < K; ++k)
                 {
                     T a = block[j][k];
                     block[j][k] = block[j][k] + imt[j][k] * ones[i];
                 }             
             }
             shiftIdentityMatrix(imt);    
         }

         for (uchar l = 0; l < K; ++l)
         {
             blocks_init[idx][l] = new T [K];
             for (uchar m = 0; m < K; ++m)
             {
                  blocks_init[idx][l][m] = block[l][m];            
             }         
         }         
                  
         squareMatrix(block);         
    }
    
    
    template <typename T>
    bool findHadamardBlocks(T ***blocks, T ***blocks_init, T **fmt)
    {
        bool equal = false;
        for (uchar i = 0; i < 4; ++i)
        {
            for (uchar j = i; j < 4; ++j)
            {
                for (uchar k = j; k < 4; ++k)
                {
                    for (uchar l = k; l < 4; ++l)
                    {
                        T **acc = new T *[K];
                        setZeroMatrix(acc, K, K);
                        
                        sumMatrices(acc, blocks[i]);
                        sumMatrices(acc, blocks[j]);
                        sumMatrices(acc, blocks[k]);
                        sumMatrices(acc, blocks[l]);
                        
                        equal = matricesAreEqual(acc, fmt);
                        if (equal)
                        {
                            hadamard_blocks[0] = blocks_init[i];
                            hadamard_blocks[1] = blocks_init[j];
                            hadamard_blocks[2] = blocks_init[k];
                            hadamard_blocks[3] = blocks_init[l];
                            return true;                        
                        }
                    } 
                                   
                }            
            }        
        }
        return false;    
    }
    
    template <typename T>
    void buildHadamardMatrix(T ***blocks_init)
    {
        for (uchar i = 0; i < ORDER; ++i)
        {
            matrix[i] = new T [ORDER];      
        }
        setZeroMatrix(matrix, ORDER, ORDER);
        
        for (int j = 0; j < K; ++j)
        {
            for (int k = 0; k < K; ++k)
            {
                
                
                //A
                matrix[j][k] = hadamard_blocks[0][j][k];
                matrix[j + K][k + K] = hadamard_blocks[0][j][k];
                matrix[j + 2 * K][k + 2 * K] = hadamard_blocks[0][j][k];
                matrix[j + 3 * K][k + 3 * K] = hadamard_blocks[0][j][k];
                
                //B -B
                matrix[j][k + K] = hadamard_blocks[1][j][k];
                matrix[j + 3 * K][k + 2 * K] = hadamard_blocks[1][j][k];
                matrix[j + K][k] = -hadamard_blocks[1][j][k];
                matrix[j + 2 * K][k + 3 * K] = -hadamard_blocks[1][j][k];
                
                //C -C
                matrix[j][k + 2 * K] = hadamard_blocks[2][j][k];
                matrix[j + K][k + 3 * K] = hadamard_blocks[2][j][k];
                matrix[j + 2 * K][k] = -hadamard_blocks[2][j][k];
                matrix[j + 3 * K][k + K] = -hadamard_blocks[2][j][k];
                
                //D -D
                matrix[j][k + 3 * K] = hadamard_blocks[3][j][k];
                matrix[j + K][k + 2 * K] = -hadamard_blocks[3][j][k];
                matrix[j + 2 * K][k + K] = hadamard_blocks[3][j][k];
                matrix[j + 3 * K][k] = -hadamard_blocks[3][j][k];
                
            }        
        }
    }
    
    
    void printHadamardMatrix()
    {
        std::cout << "Hadamard matrix of order " << ORDER << std::endl
                  << std::endl;
        printMatrix(matrix, ORDER, ORDER);
        std::cout << "Validation: " 
                  << (validateHadamard() ? " success!" : "failure!")
                  << std::endl;
    }
    
    
    bool validateHadamard()
    {
        for (ushort i = 0; i < ORDER; ++i)
        {
            for (ushort j = i + 1; j < ORDER; ++j)
            {
                if (multiplyHadamardRows(matrix[i], matrix[j]) != 0)
                    return false;
            }        
        }
        return true;
    }
    
    
    template <typename T>
    T multiplyHadamardRows(T *lrow, T *rrow)
    {
        T ret = 0;
        for (ushort i = 0; i < ORDER; ++i)
        {
            ret += lrow[i] * rrow[i];     
        }
        return ret;
    }

};


int main() 
{
    Hadamard *m = new Hadamard(2);
    m->find();
    return 0;
}