import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeSet;

class Solution {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int taskNumber = in.nextInt();
    for (int taskIdx = 1; taskIdx <= taskNumber; ++taskIdx) {
      in.next();
      int n = in.nextInt() + 1;
      BigInteger[] ps = new BigInteger[n - 1];
      for (int i = 0; i < n - 1; ++i) ps[i] = new BigInteger(in.next());
      List<Integer> idxs = new ArrayList<>(n - 2);
      for (int i = 0; i < n - 2; ++i) idxs.add(i);
      Collections.shuffle(idxs);
      BigInteger[] vs = new BigInteger[n];
      // ps[i]=vs[i]*vs[i+1]
      for (int idx : idxs) {
        BigInteger tmp = ps[idx].gcd(ps[idx + 1]);
        if (tmp.isProbablePrime(100)) {
          vs[idx + 1] = tmp;
        }
      }
      for (int i = 1; i < n; ++i) if (vs[i] == null && vs[i - 1] != null) {
        vs[i] = ps[i - 1].divide(vs[i - 1]);
      }
      for (int i = n - 2; i >= 0; --i) if (vs[i] == null && vs[i + 1] != null) {
        vs[i] = ps[i].divide(vs[i + 1]);
      }
      Set<BigInteger> ss = new TreeSet<>();
      for (int i = 0; i < n; ++i) ss.add(vs[i]);
      List<BigInteger> sortedVs = new ArrayList<>(26);
      for (BigInteger s : ss) sortedVs.add(s);
      System.out.printf("Case #%d: ", taskIdx);
      for (int i = 0; i < n; ++i) {
        System.out.print((char) ('A' + Collections.binarySearch(sortedVs, vs[i])));
      }
      System.out.println();
    }
  }
}
