#Timothy Becker, 
#start with 2D
#library(RANN);
n <- 100; #number of points
d <- 2;   #number of dimensions
data <- matrix(0,nrow=n,ncol=d); #build a dataset here
colnames(data) <- paste('X',seq(1,d,1), sep='');
for(i in 1:dim(data)[1]){
	for(j in 1:dim(data)[2]){ 
		data[i,j] <- runif(1);
	}
}
#rann_nearest <- nn2(data,data,k=5,eps=0.0);

build <- './';
apps  <- 'nn data.csv';
command <- paste(build,apps,sep='');

d_string <- paste(data,collapse=' '); #pass a data string will be the same in Python
final <- paste(command, n, d, d_string);
#write.table(data,file='',sep=',',row.names=F,col.names=F);

#cat('\nR generates numbers, runs ANN:k=5\nand generates a .CSV file to pass to NN:\n')
#cat(rann_nearest$nn.idx)
cat('\nNow NN cas been called...\n');
cpp_code <- system(final,inter=T);
cat('R has caught the stdout: \n')
cat(cpp_code)
cat('\n')

#pass it to the OpenCV app
#py_code <- system('python2.7 visualizer/CG_Test.py',inter=T)
