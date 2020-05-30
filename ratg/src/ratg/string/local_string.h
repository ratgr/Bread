#pragma once

#include <string_view>
#include <vector>

namespace ratg {

	struct local_string {
		const char* ptr;
		int size;
		bool ownsPtr;

		void own();

		local_string ref();
		local_string copy();

		operator std::string_view () {
			return std::string_view(ptr, size);
		};

		const char* data() { return ptr; }

		static local_string ref(std::string_view sv);
		static local_string ref(const char * c, int size);
		static local_string copy(std::string_view sv);
		static local_string copy(const char* c, int size);


		~local_string();
	};

	namespace impl {
		struct local_allocator_control_block {
			int size; //size = bitset_size * 4 * 8
			char bitset[1]; //bit set size in multiples of 4
			char data[0];
			
			// size as chunks of 64Bits (4 bytes) required
			//void* allocate(int size) {

			//}

			bool contains(void* ptr) {
				return ptr > data && ptr < data + size;
			}
		};

	}

	struct local_allocator {
		static constexpr int initSize = 128;
		static constexpr int maxSize = 1024;
		int blockSize;
		int blockCount = 0;
		std::vector<impl::local_allocator_control_block*> blocks;


		template<class T>
		T* alloc(int n = 1) {
			
		}

		template<class T>
		std::tuple<T*, int> allocMax(int minSize) {

		}
	};


	


}