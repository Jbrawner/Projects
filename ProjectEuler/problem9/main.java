import java.util.ArrayList;
import java.math.*;
public class main
{
    public static void main(String[] args)
    {
        BigInteger n  = 600851475143;
        Primes primes = new Primes(); 
        primes.genPrimes(50000);  
        ArrayList<Integer> list = primes.getPrimes();
        int size = primes.amtOfPrimes;
        for(int i = 0; i < size; i++)
        {
            
        }

        //primes.printSum();
        
    }

}
