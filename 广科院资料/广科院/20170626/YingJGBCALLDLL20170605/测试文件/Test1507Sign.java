package test;




import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;


import cn.tass.yingjgb.YingJGBCALLDLL;


public class Test1507Sign {

	public static void main(String[] args) throws Exception {
		
		YingJGBCALLDLL.openDevice(0); // 打开sjj1507密码机
		byte[] inData = new byte[16];
		String sign = YingJGBCALLDLL.platformCalculateSignature(0, inData);
        System.out.println("签名"+sign);
        writeSign(sign,"sign1507_1.txt");//将签名值写文件
        String sign1 = YingJGBCALLDLL.platformCalculateSignature(1, inData);
        System.out.println("签名"+sign1);
        writeSign(sign1,"sign1507_2.txt");
    	System.out.println("-----xml------------");
		inData = readFile("my.xml");
		String xmlSign = YingJGBCALLDLL.platformCalculateSignature(0, inData);
        System.out.println("xml文件签名"+xmlSign);
        writeSign(xmlSign,"sign1507_3.txt");
        YingJGBCALLDLL.closeDevice();


		
	}
	//将int类型的数据转换成为字节数组
	 public static byte[] int2bytes(int i) {
	        byte[] res = new byte[4];
	        res[0] = (byte) ((i >> 24) & 0xFF);
	        res[1] = (byte) ((i >> 16) & 0xFF);
	        res[2] = (byte) ((i >> 8) & 0xFF);
	        res[3] = (byte) (i & 0xFF);
	        return res;
	    }
	// 将byte[]转换为16进制字符串
	public static String byteToHexString(byte[] b) {
		if (b == null)
			return null;
		StringBuffer sb = new StringBuffer(b.length * 2);
		for (int i = 0; i < b.length; i++) {
			sb.append(hexStr.charAt((b[i] & 0xf0) >> 4));
			sb.append(hexStr.charAt((b[i] & 0x0f) >> 0));
		}
		return sb.toString();
	}

	private static final String hexStr = "0123456789ABCDEF";

	private static String hexString = "0123456789ABCDEF";
	
	/*
	 * 将字符串编码成16进制数字,适用于所有字符（包括中文）
	 */
	public static String encode(String str) {
	    // 根据默认编码获取字节数组
	    byte[] bytes = str.getBytes();
	    StringBuilder sb = new StringBuilder(bytes.length * 2);
	    // 将字节数组中每个字节拆解成2位16进制整数
	    for (int i = 0; i < bytes.length; i++) {
	    sb.append(hexString.charAt((bytes[i] & 0xf0) >> 4));
	    sb.append(hexString.charAt((bytes[i] & 0x0f) >> 0));
	    }
	    return sb.toString();
	}
	public static byte[] hexStringToByte(String hex) {
        if(hex==null) return null;
        int len = (hex.length() / 2);
        hex = hex.toUpperCase();
        byte[] result = new byte[len];
        char[] achar = hex.toCharArray();
        for (int i = 0; i < len; i++) {
            int pos = i * 2;
            result[i] = (byte) (toByte(achar[pos]) << 4 | toByte(achar[pos + 1]));
        }
        return result;
    }
	  private static byte toByte(int c) {
	        byte b = (byte) hexStr.indexOf(c);
	        return b;
	    }
	  
	  public static byte[] readFile(String path) throws IOException{
		  File file = new File(path);
		  FileInputStream input = new FileInputStream(file);
		  byte[] msg = new byte[(int) file.length()];
		  while(input.read(msg)!=-1){
		  }
		  input.close();
		  return msg;
	  }
	  public static void writeSign(String sign,String name) throws IOException{
		  //将签名值结果写进一个文件中
	        File f = new File(name);
	        if(!f.exists()){
	        	f.createNewFile();
	        }
	        FileWriter writer = new FileWriter(f);
	        writer.write(sign);
	        writer.flush();
	        writer.close();
	  }
}
