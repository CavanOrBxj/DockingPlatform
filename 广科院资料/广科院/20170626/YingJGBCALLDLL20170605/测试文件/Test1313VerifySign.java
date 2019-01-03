package test;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

import cn.tass.yingjgb.YingJGBCALLDLL;

public class Test1313VerifySign {
	public static void main(String[] args) throws Exception {
		YingJGBCALLDLL.openDevice(1); // 打开sjj1507密码机
		byte[] inData = new byte[16];
		for(int i=0;i<inData.length;i++){
			inData[i]=(byte) i;
		}		
		String sign = readSign("sign1313_1.txt");
		boolean b = YingJGBCALLDLL.platformVerifySignature(0, inData, sign);
		System.out.println("验证签名结果" + b);
		String sign1 = readSign("sign1313_2.txt");
		boolean b2 = YingJGBCALLDLL.platformVerifySignature(1, inData, sign1);
		System.out.println("验证签名结果" + b2);
		String xmlSign = readSign("sign1313_3.txt");
		System.out.println("-----xml------------");
		inData = readFile("my.xml");
		boolean b1 = YingJGBCALLDLL.platformVerifySignature(0, inData, xmlSign);
		System.out.println("xml验证签名结果" + b1);
        YingJGBCALLDLL.closeDevice();
		
		}
	public static String readSign(String name){
		String sign = null;
		File f = new File(name);
		if(!f.exists()){
			System.out.println("签名值文件不存在");
		}
		else{
		FileReader reader = null;
		BufferedReader breader = null;
		StringBuffer sb = null;
		try {
			reader = new FileReader(f);
		    breader = new BufferedReader(reader);
			String message = null;
			sb = new StringBuffer();
			while((message=breader.readLine()) != null){
				sb.append(message);
			}
		} catch (FileNotFoundException e) {
		} catch (IOException e) {
		}finally{
			try {
				breader.close();
				reader.close();
			} catch (IOException e) {
			}
		}
		sign = sb.toString();
	}
		return sign;
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
}
