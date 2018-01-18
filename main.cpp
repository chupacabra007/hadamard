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

    Hadamard(uchar K): K(K), ORDER(4 * K) { }
 
 
    void find()
    {
        while(true) {
            char **pmt = new char *[4];            
            setPermutationMatrix(pmt);
            
            uchar **imt = new uchar *[K];
            setIdentityMatrix(imt);            
            //printMatrix(imt, K, K);
            
            shiftIdentityMatrix(imt);
            //printMatrix(imt, K, K);
            
            uchar **imt2 = new uchar *[K];
            setIdentityMatrix(imt2);  
            
            sumMatrices(imt2, imt);
            //printMatrix(imt2, K, K);
            
            ushort **fmt = new ushort *[ORDER];
            setFinalMatrix(fmt);
            //printMatrix(fmt, ORDER, ORDER);    
            
            break;
        } 	  
    }    
    
    
private:
    const uchar K;
    const ushort ORDER;
    
    
    void setPermutationMatrix(char **arr)
    {
        for (uchar i = 0; i < 4; ++i)
        {
            arr[i] = new char[K];
            setPermutationRow(arr[i]);    	  
        }
    }
    
    
    void setPermutationRow(char *row)
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
    
    
    const uchar numOfNegatives()
    {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<uchar> uni(0, K - 1);
        return uni(rng);
    }
    
    
    void setIdentityMatrix(uchar **arr)
    {
        for (uchar i = 0; i < K; ++i)
        {
            arr[i] = new uchar[K];
            for (uchar j = 0; j < K; ++j)
            {
                arr[i][j] = 0;            
            }
            arr[i][i] = 1;  
        }
    }
    
    
    void shiftIdentityMatrix(uchar **arr)
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
    
    
    void setFinalMatrix(ushort **arr)
    {
        ushort val = K * 4;
        for (ushort i = 0; i < ORDER; ++i)
        {
            arr[i] = new ushort[ORDER];
            for (ushort j = 0; j < ORDER; ++j)
            {
                arr[i][j] = (i == j) ? val : 0;         
            }
        } 
    }
    
    
    template <typename T>
    void squareMatrix(T **arr, T **ret)
    {
        T val = 0;
        for (uchar i = 0; i < K; ++i)
        {
            ret[i] = new T[K];
            for (uchar j = 0; j < K; ++j)
            {
                val = 0;
                for (uchar k = 0; k < K; ++k) 
                {
                    val += arr[i][k] * arr[k][j];                    
                }
                ret[i][j] = val;          
            }
        }
    }
    
};


int main() 
{
    Hadamard *m = new Hadamard(3);
    m->find();
    return 0;
}