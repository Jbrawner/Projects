import java.util.ArrayList;
import java.math.*;

public class Primes
{
    private ArrayList<Integer> _primeList; // = new ArrayList<double>();
    int amtOfPrimes;
    double sum;
    public Primes()
    {
       _primeList = new ArrayList<Integer>(1000000); 
       _primeList.add(0,2);
       amtOfPrimes = 1;
       sum = 0;

    }
    public void genPrimes(int n){
       int limit = n;
       boolean prime = true;
       for(int i = 3; i < limit; i++)
       {
           prime = true;
            for(int j = 0; j < amtOfPrimes; j++)
            {
                if(i % _primeList.get(j) == 0 && prime ){
                    prime = false;
                    j = amtOfPrimes;
                }
            }
            if(prime)
            {
                sum += i;
                _primeList.add(i);
                amtOfPrimes++;
            }
       }
           

    }
    public void printPrimes()
    {
        for(int i = 0; i < amtOfPrimes; i++)
        {
            System.out.println(_primeList.get(i));
        }

    }
    public void printSum()
    {
        System.out.println("The Sum of all the primes is: " + sum);
    }
    public ArrayList<Integer> getPrimes(){
        return _primeList;
    }

}
