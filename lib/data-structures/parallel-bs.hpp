#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Parallel Binary Search — O((N + Q) log Q * op)
 * Para cada entidade em [0, N), encontra o primeiro evento
 * em [0, Q) após o qual uma condição monótona é satisfeita.
 * Requer que a condição seja monótona: uma vez satisfeita,
 * permanece.
 *
 * apl(i): aplica o evento i na estrutura de dados.
 * rlb(i): desfaz o evento i da estrutura de dados.
 * chk(i): retorna true se a entidade i satisfaz a
 *         condição dado o estado atual da estrutura.
 *
 * ans[i] = primeiro evento que satisfaz, ou -1 se nunca.
 *
 * Exemplo (soma dos setores de i >= limite[i]):
 *   ParallelBS pbs(n, q);
 *   pbs.run(
 *       [&](int i) { seg.update(l[i], r[i], {x[i]}); },
 *       [&](int i) { seg.update(l[i], r[i], {-x[i]}); },
 *       [&](int idx) {
 *           ll sum = 0;
 *           for (int s : sectors[idx]) {
 *               sum += seg.query(s, s).val;
 *               if (sum >= lim[idx]) return true;
 *           }
 *           return false;
 *       }
 *   );
 *   for (int i = 0; i < n; i++)
 *       cout << (pbs.ans[i] != -1 ? pbs.ans[i]+1 : -1);
 */

struct ParallelBS {
    int n, q;
    vector<int> ans;

    ParallelBS(int n, int q) : n(n), q(q), ans(n, -1) {}

    template <typename Apl, typename Rlb, typename Chk>
    void run(Apl apl, Rlb rlb, Chk chk) {
        vector<int> actv(n);
        iota(actv.begin(), actv.end(), 0);
        solve(0, q - 1, actv, apl, rlb, chk);
    }

  private:
    template <typename Apl, typename Rlb, typename Chk>
    void solve(int l, int r, vector<int>& actv,
               Apl apl, Rlb rlb, Chk chk) {
        if (actv.empty()) return;

        if (l == r) {
            apl(l);
            for (auto x : actv) if (chk(x)) ans[x] = l;
            rlb(l);
            return;
        }

        int mid = l + (r - l) / 2;
        for (int i = l; i <= mid; i++) apl(i);

        vector<int> pass, not_pass;
        for (auto x : actv)
            (chk(x) ? pass : not_pass).push_back(x);

        solve(mid + 1, r, not_pass, apl, rlb, chk);
        for (int i = l; i <= mid; i++) rlb(i);
        solve(l, mid, pass, apl, rlb, chk);
    }
};
