#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <ctime>
#include <algorithm>

using uchar = unsigned char;



class Hadamard {
  
public:

    Hadamard(uchar K): K(K), ORDER(4 * K) { }
 
 
    void find()
    {
    	  while(true) {
    	      char **pm = new char *[4];
    	      setPermutationMatrix(pm);
    	      break;
        } 	  
    }    
    
    
private:
    const uchar K;
    const unsigned short int ORDER;
    
    
    void setPermutationMatrix(char **arr)
    {
        for (uchar i = 0; i < 4; ++i)
    	  {
    	  	   arr[i] = new char[K];
            setPermutationRow(arr[i]);    	  
    	  }
    	    	  
        for (uchar k = 0; k < 4; ++k)
        {
            for (uchar l = 0; l < 4; ++l)
            {
                std::cout << arr[k][l] << " " ;
            }
            std::cout << std::endl;        
        }
    }
    
    
    void setPermutationRow(char *row)
    {
        const uchar num_of_negatives = numOfNegatives();
        std::vector<uchar> indices;
        
        for (uchar i = 0; i < K; ++i)
        {
        	   row[i] = 1;
        	   if (i > 0) {
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
    
};


int main() 
{
	 Hadamard *m = new Hadamard(5);
	 m->find();
    return 0;
}