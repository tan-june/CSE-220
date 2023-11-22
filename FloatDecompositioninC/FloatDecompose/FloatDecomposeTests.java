import static org.junit.Assert.assertEquals;
import org.junit.Test;

public class FloatDecomposeTests {
    
    @Test
    public void test_getSign1() {
        assertEquals(1, FloatDecompose.getSign(-93.125f));
    }

    @Test
    public void test_getSign2() {
        assertEquals(0, FloatDecompose.getSign(1.75f));
    }

    @Test
    public void test_getSign3() {
        assertEquals(0, FloatDecompose.getSign(0.578125f));
    }
    @Test
    public void test_getSign4() {
        assertEquals(1, FloatDecompose.getSign(-2323.1234345f));
    }

    @Test
    public void test_getSign5() {
        assertEquals(0, FloatDecompose.getSign(134534.73434345f));
    }

    @Test
    public void test_getSign6() {
        assertEquals(0, FloatDecompose.getSign(21313.578225f));
    }

    @Test
    public void test_getSign7() {
        assertEquals(1, FloatDecompose.getSign(-1313.578225f));
    }

    @Test
    public void test_getSign8() {
        assertEquals(0, FloatDecompose.getSign(987.577325f));
    }
    
//---------------------------------------------------------------------------------------------------------------------------------
   
    @Test
    //KMD_
    public void test_getExponent1() {
        assertEquals(133, FloatDecompose.getExponent(-93.125f));
    }
    @Test
    public void test_getExponent2() {
        assertEquals(133, FloatDecompose.getExponent(-82.457784f));
    }
    @Test
    //KMD_
    public void test_getExponent3() {
        assertEquals(127, FloatDecompose.getExponent(1.75f));
    }
    //KMD_
    @Test
    public void test_getExponent4() {
        assertEquals(126, FloatDecompose.getExponent(0.578125f));
    }
    @Test
    public void test_getExponent5() {
        assertEquals(132, FloatDecompose.getExponent(45.74234234234234f));
    }
    @Test
    public void test_getExponent6() {
        assertEquals(140, FloatDecompose.getExponent(12312.123123123f));
    }
    @Test
    public void test_getExponent7() {
        assertEquals(136, FloatDecompose.getExponent(867.345f));
    }
    @Test
    public void test_getExponent8() {
        assertEquals(136, FloatDecompose.getExponent(765.1123f));
    }
//---------------------------------------------------------------------------------------------------------------------------------
    
    @Test
    public void test_getFraction1() {
        assertEquals(3817472, FloatDecompose.getFraction(-93.125f));
    }
    @Test
    public void test_getFraction2() {
        assertEquals(6291456, FloatDecompose.getFraction(1.75f));
    }
    @Test
    public void test_getFraction3() {
        assertEquals(1310720, FloatDecompose.getFraction(0.578125f));
    }
    @Test
    public void test_getFraction4() {
        assertEquals(6346181, FloatDecompose.getFraction(28.10438f));
    } 
    @Test
    public void test_getFraction5() {
        assertEquals(838777, FloatDecompose.getFraction(8.79992f));
    } 
    @Test
    public void test_getFraction6() {
        assertEquals(1259702, FloatDecompose.getFraction(36.80538f));
    }
    @Test
    public void test_getFraction7() {
        assertEquals(5718011, FloatDecompose.getFraction(13.45312f));
    } 
    @Test
    public void test_getFraction8() {
        assertEquals(4016358, FloatDecompose.getFraction(94.64238f));
    } 
    
//---------------------------------------------------------------------------------------------------------------------------------
   
    @Test
    public void test_makeFloat1() {
        assertEquals(-93.125f, FloatDecompose.makeFloat(1, 133, 3817472), 0.0000001f);
    }

    @Test
    public void test_makeFloat2() {
        assertEquals(1.75f, FloatDecompose.makeFloat(0, 127, 6291456), 0.0000001f);
    }

    @Test
    public void test_makeFloat3() {
        assertEquals(0.578125f, FloatDecompose.makeFloat(0, 126, 1310720), 0.0000001f);
    }

    @Test
    public void test_makeFloat4() {
        assertEquals(1151.565f, FloatDecompose.makeFloat(0, 137, 1045012), 0.0000001f);
    }

    @Test
    public void test_makeFloat5() {
        assertEquals(-15.123897f, FloatDecompose.makeFloat(1, 130, 7469947), 0.0000001f);
    }

    @Test
    public void test_makeFloat6() {
        assertEquals(51.897f, FloatDecompose.makeFloat(0, 132, 5215879), 0.0000001f);
    }

    @Test
    public void test_makeFloat7() {
        assertEquals(-2.75f, FloatDecompose.makeFloat(1, 128, 3145728), 0.0000001f);
    }

    @Test
    public void test_makeFloat8() {
        assertEquals(-0.578125f, FloatDecompose.makeFloat(1, 126, 1310720), 0.0000001f);
    }

}
