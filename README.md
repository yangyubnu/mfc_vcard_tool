# mfc_vcard_tool
##MFC电话簿vcf文件和txt文件互转工具
***
####mfc_vcard_tool工具使用说明：
               本工具可以将手机vcf文件转换成可识别的txt电话本,也可以将txt电话本文件
          备份成vcf格式.以下是使用方法:
***
#####一.vcf转txt:
          打开一个vcf文件-->点击菜单栏导的出菜单-->导出成txt-->保存时默认添加后缀名,也可以自己添加.
***
***
####二.txt转vcf:
          1.打开一个保存电话号码和姓名的txt文件，文件格式如下:

                 #姓名	手机号码	移动虚拟号   
                 徐文长	13859999133	597133    (字段之间用tab符号分割)    
                 李白 , 1385999999 ;     59799    (字段之间用,或者;符号分割)         
                 "中国人", "13859999133"          ( ", " 因为",是分割符号，所以中间的空格会当作手机号码是空号，这个要注意 )
                 曹 操  , 138 5999 9999 , 999999  (字段之间用,分割,名字和号码中间可以有空格)     
                 刘 备 ,  138 5999 8888 ; 588888  (字段之间用,或者;分割,名字和号码中间可以有空格)
                 "诸葛亮", "13859999133"          ( ", " 因为",是分割符号，所以中间的空格会当作手机号码是空号，这个要注意 )
                 # (电话号码中间允许有空格)  (空格制表符分割支持)
                 # (逗号,分号引号支持) (#注释一行)


                 #####====>以"#;/"中任意一个字符开头的行表示注释行,在转换时不做处理.
                 #####====>文件总共三个字段:姓名,手机号,移动虚拟号. 字段之间必须用",;\t\n\"\'"中的任何一个
                 字符隔开,否则转换出现错误.  
**为了防止出错,建议一律使用如下格式保存电话号码(字段之间用,隔开):**

                                *#姓名     移动电话   固定电话*
                                *张三,1234567890,0987654321*
                                *李四,1234567890,0987654321*
                                *王五,1234567890,0987654321*
                                *小红,1234567890,0987654321*
                                *小明,1234567890,0987654321* 

          2.点击菜单栏的导出菜单-->导出成vcf-->保存时默认添加后缀名,也可以自己添加.
***
     
