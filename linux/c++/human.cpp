#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>



class human
{

public:
    human()
    {
         m_age = 100;
         m_name = new char(30);
         printf("m_name = %p\n",m_name);
         
    }
    
    human(int age)
    {
//         getchar();        
//         printf("m_name = %p\n",m_name);
         human();
         printf("m_name = %p\n",m_name);
         //m_age = age;
         //m_name = new char(30);
    }

    ~human()
    {
        if(m_name)
        {
        //    free(m_name);
        }
    }
    
    void show()
    {
        if(m_name)
        {
            strncpy(m_name, "r4nd0m", 6);
            *(m_name + 6) = '\0';
            printf("name:%s age:%d\n",m_name, m_age);
        }
    }
    
private:
    int m_age;
    char* m_name;
    char buf[100];
    
};


int main(int argc, char **argv)
{
    //human h;
    human h(200);
    h.show();
    return 0;
}

