# SomeTrivialNotes

1. Ipython 下直接输入
   `Image(url="https://www.***i/***.jpg", width=400, height=400)`
   图片加载不出，需要加上 `embed = True`选项,如果是data或path,则无此需要
   tutorial大法好，信息来源 http://ipython.readthedocs.io/en/stable/api/generated/IPython.display.html#module-IPython.display
   如果是matplotlib，`fig=plt.figure()`加载不出图片，需在下一行输入`plt.show()`
   参考自https://stackoverflow.com/questions/40965733/how-to-show-matplotlib-plot-from-a-figure-object

2. F=np.argmax 这个函数研究了好久，记作F(T,axis).其中T是n维tensor $t[a_1][a_2] ... [a_{axis}] ...[a_n]$

   记f=F(t,axis)

   则F(T,axis)返回一个n维tensor,$f[b_1][b_2] ... [b_i] ...[b_n]$ , 其中$b_i = a_ i \ if \ i \ !=axis \ else\ b_i = 1 $

   且有 $f[c_1][c_2] ... [c_{axis}] ...[c_n] =使得t[c_1][c_2] ... [j] ...[c_n]取得最大值的 j （c_{axis}=0,\ 0<=j<=a_{axis}-1）$

3. F=np.any类似，f=F(T,axis). T是一个$tensor[a_1][a_2] ... [a_{axis}] ...[a_n]$，

   f是一个 $tensor[a_1][a_2]...[a_{axis-1}][a_{axis+1}]...[a_{n}]$.

   ​

   ​

   ​

3. ​




```python
x = tf.placeholder(tf.float32, shape=(1024, 1024))
y = tf.matmul(x, x)

rand_array = np.random.rand(1024, 1024)
print(sess.run(y, feed_dict={x: rand_array}))  
```

