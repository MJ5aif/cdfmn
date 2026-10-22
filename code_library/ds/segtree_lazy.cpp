template<typename T>
class segTree{
public:
   int sz;
   vector<T> t;
   vector<T> lazy; 

   segTree(){}
   segTree(int l){
      sz = l;
      if (__builtin_popcount(sz) != 1){
         int x = 31 - __builtin_clz(sz);
         sz = (1LL << (x + 1));
      }

      t.assign(2 * sz + 1, 0);
      lazy.assign(2 * sz + 1, 0);
   }

   void apply(int root, int tl, int tr){
      if (!lazy[root]) return;

      t[root] += lazy[root] * (tr - tl + 1);

      if (tl != tr){
         lazy[root * 2] += lazy[root];
         lazy[root * 2 + 1] += lazy[root];
      }

      lazy[root] = 0;
   }

   T combine(const T& left, const T& right){ 
      T tm = left + right;
      return tm;
   }

   void update(int root, int tl, int tr, int l, int r, T x){ 
      apply(root, tl, tr);
      if (l > tr || r < tl) return;

      if (l <= tl && r >= tr){
         lazy[root] += x;
         apply(root, tl, tr);
         return;
      }

      int mid = (tl + tr) / 2;
      update(root * 2, tl, mid, l, r, x);
      update(root * 2 + 1, mid + 1, tr, l, r, x);

      t[root] = combine(t[root * 2], t[root * 2 + 1]);
   }

   T query(int root, int tl, int tr, int l, int r){ 
      apply(root, tl, tr);
      if (l > tr || r < tl) return 0;

      if (l <= tl && r >= tr) return t[root];

      int mid = (tl + tr) / 2;
      auto q1 = query(root * 2, tl, mid, l, r);
      auto q2 = query(root * 2 + 1, mid + 1, tr, l, r);

      return combine(q1, q2);
   }
   
   void update(int l, int r, T x){ 
      update(1, 0, sz - 1, l, r, x);
   }   

   T query(int l, int r){ 
      return query(1, 0, sz - 1, l, r);
   }
};
