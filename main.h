#include <thread>
#include <vector>
#include <functional>
#include <condition_variable>

using namespace std;

template <class ELEM_TYPE>
class MemoryPool
{
public:
  ELEM_TYPE* alloc()
  {
     return  new ELEM_TYPE;
  }
  void free(ELEM_TYPE* elem)
  {
    delete elem;
  }
};

class ThreadPool
{
  friend class MemoryPool<int>;

  private:

  vector<thread> m_vecProdThreads;
  vector<thread> m_vecConsThreads;
  vector<int*> m_vecInt;

  condition_variable m_condvar;
  mutex m_mutex;

  const int16_t MAX_VEC_SIZE;
  bool m_bStartConsThreads;
  // Create a function function
  function<void()> PThreadfunc = [&]() {
    //Do Some Important Work
     typedef MemoryPool<int> IntMemPool;
     //bool  bRemove = false;
     IntMemPool IntMem ;
     {
       lock_guard<mutex> lckgd(this->m_mutex);
       this->m_vecInt.push_back(IntMem.alloc());
       //Print Thread ID
       cout << "Thread ID : "<<this_thread::get_id() <<" inserted vector element"<<"\tVector size::"<<this->m_vecInt.size()<<endl;
       if(m_vecInt.size() == (size_t)MAX_VEC_SIZE)
       {
          this->m_bStartConsThreads = true;
          this->m_condvar.notify_all();
       }
     }
    };

    function<void()> CThreadfunc = [&]() {
    //Do Some Important Work
     typedef MemoryPool<int> IntMemPool;
     {
        //lock_guard<mutex> lckgd(this->m_mutex);
       IntMemPool IntMem ;
       unique_lock<mutex> ul(this->m_mutex);
       this->m_condvar.wait(ul, [=] {return this->m_bStartConsThreads;});

       if(m_vecInt.size() > 0)
       {
         IntMem.free(this->m_vecInt.back());
         this->m_vecInt.pop_back();
       }
       //Print Thread ID
       cout << "Thread ID : "<<this_thread::get_id() <<" removed vector element"<<"\tVector size::"<<this->m_vecInt.size()<<endl;
     }
    };

  void CreateThreadPool(uint16_t numThreads)
  {
     for(uint16_t i=0; i<numThreads;i++)
     {
       m_vecProdThreads.push_back(thread(PThreadfunc));
       m_vecConsThreads.push_back(thread(CThreadfunc));
     }
  }

  void DestroyThreadPool()
  {
     for(thread & th:m_vecProdThreads)
     {
       if(th.joinable())
       {
         //lock_guard<mutex> lckgd(m_mutex);
         //cout << endl<<"Thread ID : "<<th.get_id() <<" destroyed"<<endl;
         th.join();
       }
     }
     //cout<<"thread joined"<<endl;
     for(thread & th:m_vecConsThreads)
     {
       if(th.joinable())
       {
         //lock_guard<mutex> lckgd(m_mutex);
         //cout << endl<<"Thread ID : "<<th.get_id() <<" destroyed"<<endl;
         th.join();
       }
     }
     cout<<"thread joined"<<endl;
  }

  public:
  //function for unit test functionality
  size_t GetProdThreadPoolsize() {return m_vecProdThreads.size();}
  size_t GetConsThreadPoolsize() {return m_vecConsThreads.size();}
  size_t GetMemoryPoolsize(){ return m_vecInt.size();}

  ThreadPool(uint16_t numThreads): MAX_VEC_SIZE(5),
                                                            m_bStartConsThreads(false)
  {
    m_vecInt.reserve(MAX_VEC_SIZE);
    CreateThreadPool(numThreads);
  }

 ~ThreadPool()
  {
    DestroyThreadPool();
  }

};
