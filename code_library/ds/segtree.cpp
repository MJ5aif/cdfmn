template<typename T>
class segTree{
public:
   int sz;
   T neutral;
   vector<T> t;

   segTree(){}
   segTree(int l, T tm){
      sz=l;
      neutral=tm;
      if(__builtin_popcount(sz)!=1){
         int x=31-__builtin_clz(sz);
         sz=(1LL<<(x+1));
      }

      t.assign(((sz<<1)|1),neutral);
   }

   // need to update
   T combine(T& left, T& right){
      T tm=neutral;
      // tm=(left+right);
      return tm;
   }

   void update(int root, int tl, int tr, int pos, T x){
      if(tl==tr){
         t[root]=combine(t[root],x);
         return;
      }

      int mid=(tl+tr)/2;
      if(pos<=mid)    update((root<<1),tl,mid,pos,x);
      else            update(((root<<1)|1),mid+1,tr,pos,x);

      t[root]=combine(t[(root<<1)],t[((root<<1)|1)]);
   }

   T query(int root,  int tl, int tr, int l, int r){
      if(l>tr || r<tl)    return neutral;

      if(l<=tl && r>=tr)  return t[root];

      int mid=(tl+tr)/2;
      auto q1=query((root<<1),tl,mid,l,r);
      auto q2=query(((root<<1)|1),mid+1,tr,l,r);

      return combine(q1,q2);
   }
   
   void update(int pos, T x){
      update(1,0,sz-1,pos,x);
   }   

   T query(int l, int r){
      return query(1,0,sz-1,l,r);
   }
};
