通过查阅资料可以得知：


## Firefox

Firefox允许你在其选项窗口中启用“主密码”。你的保存的密码将使用主密码进行加密，使用密码管理器之前需要输入主密码。
Firefox Lockwise 使用端到端加密来保护用户的密码数据。这意味着即使 Mozilla（Firefox 的开发者）也无法解密用户的密码，只有用户本人可以解密和访问密码。
Firefox Lockwise 密码管理器密码存储在本地计算机上。这意味着你即使没有互联网连接也可以访问你的密码。

## Chrome

Chrome会使用Windows用户帐户密码对保存的密码进行加密。在Windows上，chrome使用dpapi.h
进行加密保护。谷歌密码管理器的安全性依赖于用户的 Google 帐户，在云服务进行保存。


