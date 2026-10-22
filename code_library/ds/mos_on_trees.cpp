struct MO_Tree{
   int n, q, B, res;

   struct query { int l, r, id, lca; };

   vector<query> Q;
   vector<int> ans, cnt;
   vector<bool> vis; 

   MO_Tree(int n, int q) : n(n), q(q) {
      res = 0;
      B = sqrt(2 * n) + 1; 
      ans.resize(q + 1);
      cnt.resize(n + 10);  
      vis.assign(n + 1, false);
   }

   void add_query(int u, int v, int id, int lca, const vector<int>& st, const vector<int>& en) {
      if (st[u] > st[v]) swap(u, v); 

      if (lca == u) {
         Q.push_back({st[u], st[v], id, -1});
      } else {
         Q.push_back({en[u], st[v], id, lca});
      }
   }

   void toggle(int node, const vector<int>& a) {
      if (vis[node]) {

      } else {

      }
      vis[node] = !vis[node]; 
   }

   void get_ans(const vector<int>& a, const vector<int>& tour) {
      sort(Q.begin(), Q.end(), [&](auto& x, auto& y) {
         if (x.l / B == y.l / B) {
            return ((x.l / B) & 1) ? x.r > y.r : x.r < y.r;
         }
         return x.l / B < y.l / B;
      });

      int L = 0, R = -1;
      
      for (auto& q : Q) {
         while (L > q.l) toggle(tour[--L], a);
         while (R < q.r) toggle(tour[++R], a);
         while (L < q.l) toggle(tour[L++], a);
         while (R > q.r) toggle(tour[R--], a);

         if (q.lca != -1) toggle(q.lca, a);

         ans[q.id] = res;

         if (q.lca != -1) toggle(q.lca, a);
      }
   }
};
