import java.math.BigInteger;

public class FloatDecompose {
    public static int getSign(float value) {
        return (Float.floatToIntBits(value)) >>> 31;
    }
    public static int getExponent(float value) {
        return (Float.floatToIntBits(value) << 1) >>> 24;
    }
    public static int getFraction(float value) {
        return (Float.floatToIntBits(value) << 9) >>> 9;
    }

    public static float makeFloat(int sign, int exp, int frac) {
        int answer = 0x0000;      
        answer |= frac;
        answer |= exp << 23;
        answer |= sign << 31; 
       return Float.intBitsToFloat(answer);
       
    }
}