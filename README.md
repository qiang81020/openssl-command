
<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [Openssl command](#openssl-command)
  - [命令总览](#命令总览)
  - [openssl man 3.0](#openssl-man-30)
  - [命令详细说明](#命令详细说明)

<!-- /code_chunk_output -->


# Openssl command
## 命令总览
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
| 33 | pkeyparam   | 公钥算法参数处理工具。<font color=green>太简单，不做详解。</font>                                                                                                                                                                  |
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
## openssl man 3.0
[openssl man 3.0](https://www.openssl.org/docs/man3.0/man1/)

## 命令详细说明
1. [ans1parse](https://github.com/qiang81020/openssl-command/blob/main/command/asym/01.asn1parse.md)

2. [ca](https://github.com/qiang81020/openssl-command/blob/main/command/asym/02.ca.md)

12. [ec](https://github.com/qiang81020/openssl-command/blob/main/command/asym/12.ec.md)

13. [ecparam](https://github.com/qiang81020/openssl-command/blob/main/command/asym/13.ecparam.md)

20. [genrsa](https://github.com/qiang81020/openssl-command/blob/main/command/asym/20.genrsa.md)

32. [pkey](https://github.com/qiang81020/openssl-command/blob/main/command/asym/32.pkey.md)

33. pkeyparam:太简单，略

34. [pkeyutl](https://github.com/qiang81020/openssl-command/blob/main/command/asym/34.pkeyutl.md)
