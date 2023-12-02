
<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [Openssl command 总览](#openssl-command-总览)
  - [1. Asymmetric Algorithm](#1-asymmetric-algorithm)
    - [1. ans1parse](#1-ans1parse)
    - [2. ans1parse](#2-ans1parse)
  - [2. Hash](#2-hash)
  - [3. Symmetric Algorithim](#3-symmetric-algorithim)
  - [命令举例](#命令举例)
  - [1. SM2相关操作](#1-sm2相关操作)
    - [1.1 SM2私钥产生](#11-sm2私钥产生)
    - [1.2 SM2签名验签](#12-sm2签名验签)
  - [2. SM3](#2-sm3)
  - [3. SM4](#3-sm4)

<!-- /code_chunk_output -->


# Openssl command 总览
## 1. Asymmetric Algorithm
| 序号 | 命令          | 介绍                                                                                                                                                                          |
|----|-------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 1  | asn1parse   | asn1格式文件解析                                                                                                                                                                  |
| 2  | ca          | ca管理                                                                                                                                                                        |
| 3  | ciphers     | 指令是用来展示用于SSL加密算法的工具。它能够把所有openssl支持的加密算法按照一定规律排列（一般是加密强度）。这样可以用来做测试工具，决定使用什么加密算法。                                                                                           |
| 4  | cmp         | 证书管理协议（CMP）是由IETF标准化的互联网协议，用于在公钥基础设施（PKI）中获取X.509数字证书。                                                                                                                      |
| 5  | cms         | 该命令处理S/MIME v3.1邮件。可以用它对S/MIME消息进行加密、解密、签名、验证签名、压缩以及解压缩等操作。                                                                                                                 |
| 6  | crl         | 管理CRL列表                                                                                                                                                                     |
| 7  | crl2pkcs7   | CRL与PKCS#7转换                                                                                                                                                                |
| 8  | dgst        | 杂凑运算命令                                                                                                                                                                      |
| 9  | dhparam     | 本指令用来维护DH的参数文件。dh命令以及gendh命令与dhparam用法大致一致                                                                                                                                  |
| 10 | dsa         | dsa 命令处理 DSA 密钥。 它们可以在各种形式之间进行转换，并打印出它们的组成部分。 注意 此命令使用传统的 SSLeay 兼容格式进行私钥加密：较新的应用程序应使用更安全的 PKCS#8 格式（使用 pkcs8）                                                              |
| 11 | dsaparam    | dsa算法参数管理                                                                                                                                                                   |
| 12 | ec          | ecc密钥本身保护、私钥计算公钥                                                                                                                                                            |
| 13 | ecparam     | ecc密钥产生                                                                                                                                                                     |
| 14 | enc         | 对称加密运算                                                                                                                                                                      |
| 15 | engine      |                                                                                                                                                                             |
| 16 | errstr      | 根据错误码查询错误内容                                                                                                                                                                 |
| 17 | fipsinstall | 执行fips配置安装                                                                                                                                                                  |
| 18 | gendsa      | 从一组参数生成DSA私钥(参数有dsaparam命令产生)                                                                                                                                               |
| 19 | genpkey     | 产生RSA、DSA、DH、EC等算法的私钥                                                                                                                                                       |
| 20 | genrsa      | RSA密钥产生                                                                                                                                                                     |
| 21 | help        |                                                                                                                                                                             |
| 22 | info        |                                                                                                                                                                             |
| 23 | kdf         | 执行密钥派生函数的操作                                                                                                                                                                 |
| 24 | list        | 列出算法和功能                                                                                                                                                                     |
| 25 | mac         | 执行计算mac操作                                                                                                                                                                   |
| 26 | nseq        | 创建或检查Netscape证书序列                                                                                                                                                           |
| 27 | ocsp        | 在线证书状态协议实用程序                                                                                                                                                                |
| 28 | passwd      | 计算密码散列。可用于生成linux password写入/etc/passwd生效                                                                                                                                   |
| 29 | pkcs12      | PKCS#12数据管理                                                                                                                                                                 |
| 30 | pkcs7       | PKCS#7数据管理                                                                                                                                                                  |
| 31 | pkcs8       | PKCS#8数据管理                                                                                                                                                                  |
| 32 | pkey        | Pkey命令处理公钥或私钥。它们可以在各种形式和打印出来的组件之间转换。                                                                                                                                        |
| 33 | pkeyparam   | 公钥算法参数处理工具                                                                                                                                                                  |
| 34 | pkeyutl     | 此命令可用于使用任何支持的算法执行低级公钥操作。可执行签名验签、加密解密（不支持sm2？）、支持sm2带id签名                                                                                                                    |
| 35 | prime       | 此命令检查指定的数字是否为素数。<br/><br/>如果命令行上没有给出数字，则应使用-generate标志根据其余标志指定的要求生成素数。                                                                                                      |
| 36 | rand        | 生成伪随机字节                                                                                                                                                                     |
| 37 | rehash      | 创建由散列值命名的文件的符号链接                                                                                                                                                            |
| 38 | req         | 证书请求签发，管理                                                                                                                                                                   |
| 39 | rsa         | rsa数据管理：密钥文件转换，对私钥进行加密、私钥生成公钥                                                                                                                                               |
| 40 | rsautl      | 公钥算法命令。此命令可用于使用任何支持的算法执行低级公钥操作。                                                                                                                                             |
| 41 | s_client    | s_client命令实现了一个通用SSL/TLS客户端，该客户端使用SSL/TLS连接到远程主机。它是SSL服务器非常有用的诊断工具。                                                                                                         |
| 42 | s_server    | 此命令实现了一个通用的SSL/TLS服务器，该服务器使用SSL/TLS监听给定端口上的连接。                                                                                                                              |
| 43 | s_time      | 此命令实现了通用SSL/TLS客户端，该客户端使用SSL/TLS连接到远程主机。它可以从服务器请求一个页面，并在其定时测量中包括传输有效负载数据的时间。它测量给定时间范围内的连接数量，传输的数据量（如果有的话），并计算一个连接的平均时间。                                                     |
| 44 | sess_id     | 此命令处理SSL会话结构的编码版本，并可选择以人类可读格式打印SSL会话详细信息（例如SSL会话主密钥）。由于这是一个需要一些SSL协议知识才能正常使用的诊断工具，因此大多数用户不需要使用它。<br/><br/>数据的精确格式可能因OpenSSL版本而异，并且没有记录在案。                                   |
| 45 | smime       | 此命令处理S/MIME邮件。它可以加密、解密、签名和验证S/MIME消息。                                                                                                                                       |
| 46 | speed       | 此命令用于测试加密算法的性能。                                                                                                                                                             |
| 47 | spkac       | 此命令处理Netscape签名的公钥和挑战（SPKAC）文件。它可以打印出其内容，验证签名，并从提供的私钥中生成自己的SPKAC。                                                                                                           |
| 48 | srp         | 此命令已弃用。它用于维护SRP（安全远程密码）文件。最多可以指定一个-add、-modify、-delete和-list选项。这些选项将零个或多个用户名作为参数，并对SRP文件执行适当的操作。对于-list，如果没有给出用户，则会显示所有用户。<br/><br/>要使用的配置文件和文件中的部分可以分别用-config和-name标志来指定。 |
| 49 | storeutl    | 此命令可用于显示从给定URI获取的内容（在解密后）。                                                                                                                                                  |
| 50 | ts          | 此命令是RFC 3161（时间戳协议，TSP）中指定的基本时间戳权限（TSA）客户端和服务器应用程序。TSA可以成为PKI部署的一部分，其作用是在特定时间之前提供特定数据存在的长期证据。以下是协议的简要描述：                                                                    |
| 51 | verify      | 此命令验证证书链。如果证书链有多个问题，该程序会尝试显示所有问题。                                                                                                                                           |
| 52 | version     |                                                                                                                                                                             |
| 53 | x509        | 证书显示、格式转换、CSR签名                                                                                                                                                             |

### 1. ans1parse

### 2. ans1parse

## 2. Hash

## 3. Symmetric Algorithim

## 命令举例
## 1. SM2相关操作

### 1.1 SM2私钥产生

1. 查看所支持的曲线(主要看是否支持SM2曲线)

```bash
openssl ecparam -list_curves
```

>...
brainpoolP384t1: RFC 5639 curve over a 384 bit prime field
brainpoolP512r1: RFC 5639 curve over a 512 bit prime field
brainpoolP512t1: RFC 5639 curve over a 512 bit prime field
SM2       : SM2 curve over a 256 bit prime field

2. 产生SM2私钥

```bash
openssl ecparam -name SM2 -genkey -out sm2-sk.pem

cat sm2-sk.pem

>root@5c9a65ae235f:~/sm2# cat sm2-sk.pem
-----BEGIN SM2 PARAMETERS-----
BggqgRzPVQGCLQ==
-----END SM2 PARAMETERS-----
-----BEGIN PRIVATE KEY-----
MIGIAgEAMBQGCCqBHM9VAYItBggqgRzPVQGCLQRtMGsCAQEEIGr+lQLj0nTtzXiC
/d/IySg6C1FA0z4LQoEZVMtfAdx7oUQDQgAE/IIzlhOCtGQr9ixE2EDyhZB/cfva
9vr4Ivi1PzqtwKtQ3rz8lcGBhgS81kOTzyVewfpZDxehWJdOup0lj3iEdA==
-----END PRIVATE KEY-----
```

3. 根据私钥产生公钥

```bash
openssl ec -in sm2-sk.pem -pubout -out sm2-pk.pem

root@5c9a65ae235f:~/sm2# openssl ec -in sm2-sk.pem -pubout -out sm2-pk.pem
read EC key
writing EC key
```

### 1.2 SM2签名验签 
1. 生成2进制文件
```bash
echo 112233 | xxd -r -p > p.bin

root@5c9a65ae235f:~/sm2# xxd p.bin 
00000000: 1122 33                                  ."3
```

2. 对文件计算sm2-sm3签名
```bash
openssl dgst -SM3 -sign sm2-sk.pem -out sm2_ec.sig p.bin 
```

3. 浏览生成的签名文件
```bash
openssl asn1parse -inform DER -in sm2_ec.sig

root@5c9a65ae235f:~/sm2# openssl asn1parse -inform DER -in sm2_ec.sig
    0:d=0  hl=2 l=  68 cons: SEQUENCE          
    2:d=1  hl=2 l=  32 prim: INTEGER           :292371A3A76B1AF410FE043B99ACA7EAADF393F44E327E46EED7C2AE011ED524
   36:d=1  hl=2 l=  32 prim: INTEGER           :4B94607A35414EDFB652835F54D469477AC0571BE2593B1EBD64C382BBBEB981
```

4. 使用sm2-sm3验证签名
```bash
openssl dgst -SM3 -verify sm2-pk.pem -signature sm2_ec.sig p.bin

root@5c9a65ae235f:~/sm2# openssl dgst -SM3 -verify sm2-pk.pem -signature sm2_ec.sig p.bin
Verified OK
```

## 2. SM3
```bash
openssl dgst -SM3 p.bin

root@5c9a65ae235f:~/sm2# openssl dgst -SM3 p.bin
SM3(p.bin)= 1ec39ca0fdc96a2f57e8b2af0b93df343455526287619b316ca515158697388f
```
## 3. SM4
1. 生成原文件
```bash
echo 11223344556677889900AABBCCDDEEFF | xxd -r -p > plain.bin

root@5c9a65ae235f:~/sm2# echo 11223344556677889900AABBCCDDEEFF | xxd -r -p > plain.bin
root@5c9a65ae235f:~/sm2# xxd plain.bin 
00000000: 1122 3344 5566 7788 9900 aabb ccdd eeff  ."3DUfw.........
```

2. 加密文件
```bash
openssl enc -sm4-cbc -iv 11223344556677889900AABBCCDDEEFF -K 000102030405060708090A0B0C0D0E0F -in plain.bin -out cipher.bin -nopad

root@5c9a65ae235f:~/sm2# openssl enc -sm4-cbc -iv 11223344556677889900AABBCCDDEEFF -K 000102030405060708090A0B0C0D0E0F -in plain.bin -out cipher.bin -nopad
root@5c9a65ae235f:~/sm2# xxd cipher.bin 
00000000: 1e96 34b7 70f9 aeba a934 4f5a ff9f 82a3  ..4.p....4OZ....
```

3. 解密文件
```bash
openssl enc -d -sm4-cbc -iv 11223344556677889900AABBCCDDEEFF -K 000102030405060708090A0B0C0D0E0F -in cipher.bin -out plain-1.bin -nopad

root@5c9a65ae235f:~/sm2# openssl enc -d -sm4-cbc -iv 11223344556677889900AABBCCDDEEFF -K 000102030405060708090A0B0C0D0E0F -in cipher.bin -out plain-1.bin -nopad
root@5c9a65ae235f:~/sm2# xxd plain-1.bin 
00000000: 1122 3344 5566 7788 9900 aabb ccdd eeff  ."3DUfw.........
```