// Crack code 13.8
//
#include <cstdio>
#include "malloc.h"

template <class T> class SmartPointer{
	
	public:

		// 普通指针转成智能指针
		SmartPointer(T * ptr){
			ref = ptr;
			ref_count = (unsigned*)malloc(sizeof(unsigned));
			*ref_count = 1;
		}

		// 复制构造
		// Person p(q);
		// Person p = q;
		// f(p); //值传递
		// 
		SmartPointer(SmartPointer<T> & sptr){
			ref = sptr.ref;
			ref_count = sptr.ref_count;
			++(*ref_count);
		}

		// p = q
		SmartPointer<T> & operator=(SmartPointer<T> & sptr){
			if (this == &sptr) {
				return *this;
			}
			if (*ref_count > 0){ // p已经有引用了
				remove(); // 删除原先的引用
			}

			ref = sptr.ref; // 新引用
			ref_count = sptr.ref_count; // 新引用计数
			++(*ref_count);
			return *this;
		}

		~SmartPointer(){
			remove();
		}

		T getValue(){
			return *ref;
		}
		unsigned getRefCnt(){
			return *ref_count;
		}
	private:
		void remove(){ // 删掉一个引用
			--(*ref_count);
			if (*ref_count == 0){ // 无引用，可释放
				delete ref;
				free(ref_count);
				ref = NULL;
				ref_count = NULL;
			}
		}

		T * ref;
		unsigned * ref_count;
};

int main(int argc, char* argv[])
{
	printf("Hello world\n");
	SmartPointer<int> sp(new int(2));
	printf("cnt: %d\n", sp.getRefCnt());
	SmartPointer<int> sp2 = sp;
	printf("cnt: %d\n", sp.getRefCnt());
	printf("cnt: %d\n", sp2.getRefCnt());

	int x;
	scanf("%d", &x);
	return 0;
}

