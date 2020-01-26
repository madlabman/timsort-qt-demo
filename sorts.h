#ifndef SORTS
#define SORTS

namespace sort {

template <class T>
T* insertSort(T *arr, int n)
{
    for (int i = 1; i < n; i++)
        for(int j = i; j > 0 && arr[j-1] > arr[j]; j--)
            std::swap(arr[j-1], arr[j]);
}


// Слияние двух массивов
template<class T> void Merge(T const *const A, int const nA,
                             T const *const B, int const nB,
                             T *const C)
{ //Выполнить слияние массива A, содержащего nA элементов,
  //  и массива B, содержащего nB элементов.
  //  Результат записать в массив C.

    int a(0), b(0); //Номера текущих элементов в массивах A и B

    while( a+b < nA+nB ) //Пока остались элементы в массивах
    {
        if( (b>=nB) || ( (a<nA) && (A[a]<=B[b]) ) )
        { //Копирую элемент из массива A
            C[a+b] = A[a];
            ++a;
        } else { //Копирую элемент из массива B
            C[a+b] = B[b];
            ++b;
        }
    }
}

// Функция восходящего слияния
template <class T>
void mergeSort(T * mas, int len)
{
    int n = 1, l, ost;
    T * mas1;
    while (n < len) {
        l = 0;
        while (l < len) {
            if (l + n >= len) break;
            ost = (l + n * 2 > len) ? (len - (l + n)) : n;
            mas1 = merge(mas + l, mas + l + n, n, ost);
            for (int i = 0; i < n + ost; ++i)
                mas[l+i] = mas1[i];//тут нужно что-то поменять, потому что это лишнее копирование, и оно увеличивает время работы алгоритма в два раза
            delete [] mas1;
            l += n * 2;
        }
        n *= 2;
    }
}
}


namespace Timsort
{
    struct segment {
      int beg; // индекс первого элемента
      int len; // длина интервала
      segment(){}
      segment(int b, int l) : beg(b), len(l){}
    };
    // ответ должен быть в диапазоне (32,64]
    inline int get_min_size(int n) {
      int r = 0;
      while (n >= 64) {
        n >>= 1;
        r |= n &1;
      }
      return n + r;
    }

    template <class T>
    void insertSort(T &arr, int beg, int last)
    {
        for (int i = beg + 1; i < last; i++)
            for(int j = i; j > beg && arr[j-1] > arr[j]; j--)
                std::swap(arr[j-1], arr[j]);
    }

    const int dx = 1, dy = 2, dz = 3;

    void merge(std::vector<int> &mas, std::vector<segment> &seg, bool isXY, std::vector<int> &tmp) {
      segment f = seg[seg.size() - dy];
      segment s = isXY ? seg[seg.size() - dx] : seg[seg.size() - dz];
      if (f.beg > s.beg) std::swap(f,s);
      int posF = 0, posS = s.beg, pos = f.beg-1;
      int lstF = f.len, lstS = s.beg + s.len;
      copy(mas.begin() + f.beg + posF, mas.begin() + f.beg + lstF, tmp.begin());
      int fAmount = 0, sAmount = 0;
      while (posF < lstF && posS < lstS) {
        if (tmp[posF] < mas[posS]) {
          mas[++pos] = tmp[posF++];
          ++fAmount; sAmount=0;
          if (fAmount == 7) {
            std::vector<int>::iterator it = upper_bound(tmp.begin() + posF, tmp.begin() + lstF, mas[posS]);
            copy(tmp.begin() + posF, it, mas.begin() + pos + 1);
            pos += it - (tmp.begin() + posF);
            posF += it - (tmp.begin() + posF);
          }
        }
        else {
          mas[++pos] = mas[posS++];
          fAmount=0; ++sAmount;
          if (sAmount == 7) {
            std::vector<int>::iterator it = upper_bound(mas.begin() + posS, mas.begin() + lstS, tmp[posF]);
            copy(mas.begin() + posS, it, mas.begin() + pos + 1);
            pos += it - (mas.begin() + posS);
            posS += it - (mas.begin() + posS);
          }
        }
      }
      copy(tmp.begin() + posF, tmp.begin() + lstF, mas.begin() + pos + 1);
    }

    void try_merge(std::vector<int> &mas, std::vector<segment> &seg, std::vector<int> &tmp, bool is_merge = false) {
      while (seg.size() > 1) {
        int x = seg[seg.size() - dx].len;
        int y = seg.size() < 2 ? 0 : seg[seg.size() - dy].len;
        int z = seg.size() < 3 ? 0 : seg[seg.size() - dz].len;
        if (seg.size() >= 3 && z <= x + y) {
          if (z < x) {
            merge(mas,seg,false,tmp);
            seg[seg.size() - dz].len += seg[seg.size() - dy].len;
            seg[seg.size()- dy] = seg[seg.size()- dx];
            goto POP_BACK;
          }
          else {
            merge(mas,seg,true,tmp);
            seg[seg.size() - dy].len += seg[seg.size() - dx].len;
            goto POP_BACK;
          }
        }
        else if (is_merge || y <= x) {
          merge(mas,seg,true,tmp);
          seg[seg.size() - dy].len += seg[seg.size() - dx].len;
          goto POP_BACK;
        }
        else
          break;
    POP_BACK: seg.pop_back();
      }
    }

    void tim_sort(std::vector<int> &mas) {
      int n = mas.size();
      std::vector<int> tmp(n);
      int min_size = get_min_size(n);
      int beg = 0, size = min_size;
      std::vector<segment> seg;
      seg.reserve((n-1)/min_size + 1);

      for (int i=0;i<n;i+=min_size) {
        size = std::min(min_size,n-i);
        insertSort(mas,i,i+size);
        seg.push_back(segment(i,size));
        try_merge(mas, seg, tmp);
      }
      while (seg.size() != 1) {
        try_merge(mas, seg, tmp, true);
      }
    }

}






#endif // SORTS

