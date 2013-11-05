#Timothy Becker, 
#start with 2D
library(RANN);

n <- 100; #number of points
d <- 2;   #number of dimensions
data <- matrix(0,nrow=n,ncol=d); #build a dataset here
colnames(data) <- paste('X',seq(1,d,1), sep='');
for(i in 1:dim(data)[1]){
	for(j in 1:dim(data)[2]){ data[i,j] <- runif(1); }
}
rann_nearest <- nn2(data,data,k=5,eps=0.0);
build <- './dist/Debug/GNU_4.8-MacOSX/';
write.table(data,file=paste(build,'data.csv',sep=''),sep=',',row.names=F,col.names=T);
cat('\nR generates numbers, runs ANN:k=5\nand generates a .CSV file to pass to NN:\n')
cat(rann_nearest$nn.idx)
cat('\nNow NN cas been called...\n');
cpp_code <- system(paste(build,'nn data.csv',sep=''),intern=T)
cat('R has caught the stdout: \n')
cat(cpp_code)
cat('\n')
