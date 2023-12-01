[toc]
# openssl command 总览
| 序号 | 命令          | 介绍                                                                                |
|----|-------------|-----------------------------------------------------------------------------------|
| 1  | asn1parse   | asn1格式文件解析                                                                        |
| 2  | ca          | ca管理                                                                              |
| 3  | ciphers     | 指令是用来展示用于SSL加密算法的工具。它能够把所有openssl支持的加密算法按照一定规律排列（一般是加密强度）。这样可以用来做测试工具，决定使用什么加密算法。 |
| 4  | cmp         | 证书管理协议（CMP）是由IETF标准化的互联网协议，用于在公钥基础设施（PKI）中获取X.509数字证书。                            |
| 5  | cms         | 该命令处理S/MIME v3.1邮件。可以用它对S/MIME消息进行加密、解密、签名、验证签名、压缩以及解压缩等操作。                       |
| 6  | crl         | 管理CRL列表                                                                           |
| 7  | crl2pkcs7   | CRL与PKCS#7转换                                                                      |
| 8  | dgst        | 杂凑运算命令                                                                            |
| 9  | dhparam     | 本指令用来维护DH的参数文件。dh命令以及gendh命令与dhparam用法大致一致                                        |
| 10 | dsa         |                                                                                   |
| 11 | dsaparam    |                                                                                   |
| 12 | ec          | ecc密钥本身保护、私钥计算公钥                                                                  |
| 13 | ecparam     | ecc密钥产生                                                                           |
| 14 | enc         | 对称加密运算                                                                            |
| 15 | engine      |                                                                                   |
| 16 | errstr      |                                                                                   |
| 17 | fipsinstall |                                                                                   |
| 18 | gendsa      |                                                                                   |
| 19 | genpkey     |                                                                                   |
| 20 | genrsa      | RSA密钥产生                                                                           |
| 21 | help        |                                                                                   |
| 22 | info        |                                                                                   |
| 23 | kdf         |                                                                                   |
| 24 | list        |                                                                                   |
| 25 | mac         |                                                                                   |
| 26 | nseq        |                                                                                   |
| 27 | ocsp        |                                                                                   |
| 28 | passwd      |                                                                                   |
| 29 | pkcs12      | PKCS#12数据管理                                                                       |
| 30 | pkcs7       | PKCS#7数据管理                                                                        |
| 31 | pkcs8       | PKCS#8数据管理                                                                        |
| 32 | pkey        |                                                                                   |
| 33 | pkeyparam   |                                                                                   |
| 34 | pkeyutl     |                                                                                   |
| 35 | prime       |                                                                                   |
| 36 | rand        |                                                                                   |
| 37 | rehash      |                                                                                   |
| 38 | req         | 证书请求签发，管理                                                                         |
| 39 | rsa         | rsa数据管理：密钥文件转换，对私钥进行加密、私钥生成公钥                                                     |
| 40 | rsautl      |                                                                                   |
| 41 | s_client    |                                                                                   |
| 42 | s_server    |                                                                                   |
| 43 | s_time      |                                                                                   |
| 44 | sess_id     |                                                                                   |
| 45 | smime       |                                                                                   |
| 46 | speed       |                                                                                   |
| 47 | spkac       |                                                                                   |
| 48 | srp         |                                                                                   |
| 49 | storeutl    |                                                                                   |
| 50 | ts          |                                                                                   |
| 51 | verify      |                                                                                   |
| 52 | version     |                                                                                   |
| 53 | x509        | 证书显示、格式转换、CSR签名                                                                   |
## 1. ans1parse