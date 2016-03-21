//Needs way too much time to run.
import java.util.ArrayList;
import java.util.HashMap;
public class main
{
    public static void main(String[] args)
    {
       int i = 0; 
       int n = 0; 
       int curr = 0; 
       ArrayList<Integer> divs = new ArrayList<Integer>(250);
       HashMap <Integer, Integer> mem = new HashMap<Integer, Integer>();
       while(n <= 500)
       {
           n = 1;//counting itself in this
           curr+= i++;
           int limit = curr/2;
           //System.out.println("Curr: " + curr);
           if((curr % 2) == 0 )
           {
               for(int j = 1; j <= limit ; j++)//itself is a divisor
               {
                   if((curr % j ) == 0)
                   {
                       n++;
                   }
               }
           }
           //System.out.println("n: " + n);
       }
       System.out.println("Answer: " + curr);
    }
}
