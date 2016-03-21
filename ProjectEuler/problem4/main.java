public class main {
    public static void main(String[] args){
        int first, second, largest = 0;
        for (int i = 100; i < 999; i++){
            for(int j = 100; j < 999; j++){
               first = i * j; 
               second = reverseInt(first);
                if(first == second){
                   if(largest < first){
                       largest = first;
                   }
                }
            }
        }
        System.out.println(largest);
    }
    public static int reverseInt(int n)
    {
        int reverse = 0;
        while( n != 0 )
        {
            reverse = reverse * 10;
            reverse = reverse + n%10;
            n = n/10;
        }
        return reverse;
    }
}

