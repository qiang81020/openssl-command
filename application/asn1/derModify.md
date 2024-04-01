# 修改（对比)der文件内容

## 步骤

1. 将der或pem文件转化为asn1parse可识别的config文件（带数据）
2. 在config文件修改数据的值
3. 使用-genconf生成新的der文件

### 使用asn1template脚本进行转换

[asn1parse github](https://github.com/wllm-rbnt/asn1template)

### 修改config文件数据部分

文件基本结构不变，可以根据需要修改内容的部分

### 使用-genconf标识生成修改后的der文件

```bash
openssl asn1parse -genconf file.tpl -out file.der
```
