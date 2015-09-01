#include<iostream>
#include<random>
#include<vector>
#include<ctime>
#include<math.h>
#include<iomanip>

void clustering();
int smallest_index(float*arr,int size);
int main(){
	clustering();
	return 0;
}

void clustering(){
	int cluster_no;
	std::cout << "Number of clusters: " << std::endl;
	std::cin >> cluster_no;
	int dataSetNo;//number of data set
	std::cout << "number of data sets: " << std::endl;
	std::cin >> dataSetNo;

	//std::pair<float, float>set;
	srand(time(NULL));//seeding 
	std::vector<std::pair<float, float>> data_set(dataSetNo);
	std::vector<std::pair<float, float>> centroids(cluster_no);
	std::vector<std::vector<int>> clusters(cluster_no);//to assign point index to index of cluster

	int*pointsInCluster = new int[cluster_no]; //to count points in each cluster
	int *pointsInCluster_loop = new int[cluster_no];
	
	int loop = 0;
	bool loopAgain = false;
	bool change = true;

	for (int i = 0; i < dataSetNo; i++)//generating data set randomly
	{
		data_set[i].first = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100.0f)); //random floates 0->100
		data_set[i].second = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100.0f));
	}

	for (int i = 0; i < cluster_no; i++)//random positions for centroids
	{
		centroids[i].first = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100.0f));
		centroids[i].second = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100.0f));
	}

	do
	{
		for (int i = 0; i < cluster_no;i++)
		clusters[i].clear();
		
		for (int i = 0; i < dataSetNo; i++)//cluster assigning //i for data set index, j for clusters index
		{
			float*tmp = new float[cluster_no];
			int tmp_index = 0;
			for (int j = 0; j < cluster_no; j++)
			{
				//distance=sqrt( (x2-x1)^2 + (y2-y1)^2 )
				//	tmp[j] = sqrtf(abs(powf(data_set[i].first - centroids[j].first, 2.0f) + abs((powf(data_set[i].second - centroids[j].second, 2)))));
				tmp[j] = sqrtf(powf(data_set[i].first - centroids[j].first, 2.0f) + (powf(data_set[i].second - centroids[j].second, 2)));
			}
			tmp_index = smallest_index(tmp, cluster_no); //finding index of smalled distance
			clusters[tmp_index].push_back(i); //assigned the point to the nearest cluster

			delete[]tmp;
			tmp = NULL;
		}

		//updating centroids position


		for (int i = 0; i < cluster_no; i++){
			int tmp_index = 0;
			float mean_x = 0;
			float mean_y = 0;
			pointsInCluster_loop[i] = clusters[i].size();
			for (int j = 0; j < clusters[i].size(); j++){
				// mean += clusters[i][j];
				tmp_index = clusters[i][j];
				mean_x += data_set[tmp_index].first;
				mean_y += data_set[tmp_index].second;
			}
			//mean /= clusters[i].size; 
			mean_x /= clusters[i].size();
			mean_y /= clusters[i].size();
			centroids[i].first = mean_x;
			centroids[i].second = mean_y;
		}
		if (change)
		{
			for (int i = 0; i < cluster_no; i++)//want it in the first time only
				pointsInCluster[i] = clusters[i].size();
			change = false;
		}
		if (loop > 0)
		{
			for (int i = 0; i < cluster_no; i++)
				if (pointsInCluster[i] != pointsInCluster_loop[i])
				{
				pointsInCluster[i] = pointsInCluster_loop[i];
				loopAgain = true;
				}
				else
					loopAgain = false;
			//change = true;
		}
		loop++;
	} while (loop<2 || loopAgain);

	std::cout << "Clusters: " << std::endl;
	for (int i = 0; i < cluster_no; i++)
	{
		std::cout << "\nCluster #" << i+1 << "(" <<std::setprecision(4)<<centroids[i].first<<
			","<<std::setprecision(4)<<centroids[i].second<<")\n"<<std::endl;

		for (int j = 0; j < clusters[i].size(); j++)
		{
			std::cout <<"Point#"<<clusters[i][j]+1<< "(" <<std::setprecision(4)<< data_set[clusters[i][j]].first << 
				"," << std::setprecision(4) << data_set[clusters[i][j]].second << ")\n";
		}
		std::cout<<std::endl;
	}
}
int smallest_index(float*arr,int size)
{
	int index = 0;

	for (int i = 1; i <size ; i++)
	{
		if (arr[i] < arr[index])
			index = i;
	}

	return index;
}