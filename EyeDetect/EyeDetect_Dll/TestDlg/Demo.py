print ("Hello Word")

def DoubleINT(x):
    if(x>0):
        return  x+x
    elif(x<0):
        return  abs(x)+abs(x)       
    return 0


#输入数据
Num=input("Please Input Num: ")
print("Input Num is %d"%(int(Num)))

#获取Num的数据类型
print("Num is %s"%(type(Num)))

#强制转换
iNum=int(Num)
print("Num is %s"%(type(iNum)))

iNum=DoubleINT(iNum)
print("Input Num is %d"%(iNum))

#显示对话框
import tkinter
top=tkinter.Tk()
label=tkinter.Label(top, text='hello')
label.pack()
tkinter.mainloop()

#等待输入
input()
