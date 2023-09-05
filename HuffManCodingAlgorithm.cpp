#include<iostream>
#include<string>
#include<map>
#include<algorithm>
#include<queue>

using namespace std;

struct Node
{
    char ch;
    int freq;
    Node* left;
    Node* right;
    Node(char c,int f, Node*l = NULL,Node* r = NULL)
    {
        ch = c;
        freq = f;
        left = l;
        right = r;
    }
};

struct compare
{
    bool operator () (Node* L,Node* R)
    {
        return L->freq < R->freq;
    }
};

class HuffmanAlgorithm
{
    
  private:
      string input,encodedString,decodedString;
      map<char,int> frequencyMap;
      map<char,string> codes;
      priority_queue<Node*,vector<Node*>,compare> pq;
      Node* huffmanTreeRoot;
      
 public :
      HuffmanAlgorithm(string input)
      {
          this->input = input;
      }
      void doFindFrequency()
      {
         
          for(char ch : input)
          {
              frequencyMap[ch]++;
          }
          //cout<<"Find Frequency called :"<<frequencyMap.size()<<endl;
      }
      void createMinHeap()
      {
          for(auto it : frequencyMap)
          {
              char ch = it.first; 
              int freq = it.second;
              //cout<<ch<<" "<<freq<<endl;
              pq.push(new Node(ch,freq));
          }
          //cout<<"createMinHeap called : "<<pq.size()<<endl;
         // priority_queue<Node*,vector<Node*>,compare> dummy = pq;
         // while(dummy.size())
         // {
           //   cout<<dummy.top()->ch<<" "<<dummy.top()->freq<<endl;
           //   dummy.pop();
          //}
      }
      void createHuffManTree()
      {
          while(pq.size() > 1)
          {
              Node* left = pq.top(); pq.pop();
              Node* right = pq.top(); pq.pop();
              //cout<<left->ch<<left->freq<<" "<<right->ch<<right->freq<<endl;
              Node* temp = new Node('*',left->freq + right->freq,left,right);
              //cout<<"node created "<<endl;
              pq.push(temp);
          }
          
          //cout<<"createHuffManTree called ! Huffman root :" <<pq.top()->ch<<"."<<endl;
          createCodes(pq.top(),"");
      }
      void createCodes(Node* root,string str)
      {
          
          if(root->ch != '*')
          {
              //cout<<"create codes :"<<root->ch<<" "<<str<<endl;
              codes[root->ch] = str;
              return;
          }
          createCodes(root->left,str + "0");
          createCodes(root->right,str + "1");
      }
      void createEncodedString()
      {
          for(char ch : input)
          {
              string temp = codes[ch];
              encodedString += temp;
          }
          cout<<"createEncodedString called : "<<encodedString<<endl;
          
      }
      void doStartEncoding()
      {
          doFindFrequency();
          createMinHeap();
          createHuffManTree();
          
          createEncodedString();
      }
      void doStartDecoding()
      {
          Node* curr= pq.top();
          for(char ch : encodedString)
          {
              if(ch == '0')
              {
                  curr = curr->left;
              }
              else if(ch == '1')
              {
                  curr = curr->right;
              }
              if(!curr->left && !curr->right)
              {
                  cout<<curr->ch;
                  curr = pq.top();
              }
          }
          
      }
};


int main()
{
    HuffmanAlgorithm h("abdkcljldjfakljdsf123456789");
    h.doStartEncoding();
    cout<<endl;
    h.doStartDecoding();
    return 0;
}

// 10101111110000
// 10101111110000


















