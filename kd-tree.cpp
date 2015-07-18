#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
typedef vector< vector< double > > data_t;
typedef vector< double > vec_t;
typedef struct Point{
	int dim;
	int split;
	vec_t node;
	Point *left, *right, *parent;
	Point(){
		this->dim = -1;
		this->split = -1;
		this->left = NULL;
		this->right = NULL;
		this->parent = NULL;
	}
	~Point(){
		this->node.clear();
		if (this->left)
			delete this->left;
		this->left = NULL;
		if (this->right)
			delete this->right;
		this->right = NULL;
		this->parent = NULL;
	}
	void print(){
		for (size_t i = 0; i < this->node.size(); i++)
			printf("%lf ", this->node.at(i));
		printf("\n");
	}
}point_t, *point;
double variation(data_t &dataset, size_t split){
	data_t::iterator i;
	double mean = 0;
	double variation = 0;
	for (i = dataset.begin(); i != dataset.end(); i++){
		mean += i->at(split);
	}
	mean /= dataset.size();
	for (i = dataset.begin(); i != dataset.end(); i++){
		variation += pow(i->at(split) - mean, 2.0);
	}
	variation /= dataset.size();
	return variation;
}
void construct(point &root, data_t dataset){
	if (dataset.size() == 0)
		return;
	root = new point_t();
	vector< double > buff;
	for (size_t i = 0; i < dataset.at(0).size(); i++){
		buff.push_back(variation(dataset, i));
	}
	size_t split = 0;
	double min;
	for (size_t i = 0; i < buff.size(); i++){
		if (i == 0){
			min = buff.at(i);
		}
		else{
			if (min < buff.at(i)){
				min = buff.at(i);
				split = i;
			}
		}
	}
	sort(dataset.begin(), dataset.end(), [split](vec_t a, vec_t b){ return a.at(split) < b.at(split); });
	size_t middle = dataset.size() / 2;
	root->split = split;
	for (size_t i = 0; i < dataset.at(middle).size(); i++){
		root->node.push_back(dataset.at(middle).at(i));
	}
	root->dim = root->node.size();
	data_t lDataset, rDataset;
	for (size_t i = 0; i < middle; i++){
		lDataset.push_back(dataset.at(i));
	}
	for (size_t i = middle + 1; i < dataset.size(); i++){
		rDataset.push_back(dataset.at(i));
	}
	construct(root->left, lDataset);
	construct(root->right, rDataset);
	if (root->left)
		root->left->parent = root;
	if (root->right)
		root->right->parent = root;
	return;
}
void inOrder(point root){
	if (root){
		root->print();
		inOrder(root->left);
		inOrder(root->right);
	}
	return;
}
int main(){
	data_t data;
	FILE *fp = NULL;
	char buff[1000];
	if (fp = fopen("data.txt", "r")){
		while (fgets(buff, 1000, fp)){
			double x, y;
			sscanf(buff, "%lf%lf", &x, &y);
			vec_t vec;
			vec.push_back(x);
			vec.push_back(y);
			data.push_back(vec);
		}
		point root = NULL;
		construct(root, data);
		inOrder(root);
		fclose(fp);
		delete root;
	}
	return 0;
}