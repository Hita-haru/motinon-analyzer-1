# **git push origin main禁止！！**
詳細はplan.mdを参照  
2026/05/05よりあとのmainへのpushは禁止。それ以前は咎めません。  
もしgit push origin mainをしてしまったら...  
- 一度だけやらかしたとき（最後のpushがgit push origin main）  
```
git revert HEAD --no-edit
git push origin main
```
- 何回もやらかしたりやらかしたあとに他のbranchにpushをしたとき  
やってくれたね  
PM（@Hita-haru）へ連絡を  

# Motion-analyzer-1 (Motiana1)
## 共同開発者へ
制作予定のプログラムについては./plan.mdに記述しているため、開発前に必ず./plan.mdを参照すること。
