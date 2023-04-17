#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
using namespace std;

//templatized single linked list
template <typename T>
struct node
{
	//Data Members
	T data;
	node* next;

	//Member Functions

	node()   //Default Constructor
	{
		next = NULL;
	}
};

template<typename T>
class LinkList
{
	//Data Members
	node <T>* head;
	node <T>* tail;
	int size;

public:

	//Member Functions 

	LinkList()  //Default Constructor
	{
		head = tail = NULL;
		size = 0;
	}

	void addingnodeinEND(T newData)
	{
		bool repetition_check = false;      // flag to keep track of not repeating values in the link list

		node <T>* traverse_temp = head;    // temporary node creation for traversal

		for (int i = 1; i <= size; i++)      // loop iterates till all the values in link list are checked
		{
			if (traverse_temp->data == newData)   // consition to check if any data matches
			{
				repetition_check = true;    // if data matches then set repetition flag to true
				return;                       // return as soon as any value matches
			}
			traverse_temp = traverse_temp->next;  // update temporary traversal node with succeeding node in each iteration
		}

		if (repetition_check == false)     //Node addition to be done only if no previously added data matches with the newly added to be one.
		{
			node<T>* temp = new node<T>;   //Temporary node creation
			temp->data = newData;            //Initializing data of temp with the passed parameter
			temp->next = NULL;               //Setting next to Null for temp

			if (head == NULL)      //Incase the head is Null
			{
				head = tail = temp;    //Initialize both head and tail with temp
				size++;                //Incrementing size variable to keep track of size of the link list
			}
			else
			{
				tail->next = temp;  //If head is not empty then update tail with new node
				tail = tail->next;
				size++;         //Incrementing size variable to keep track of size of the link list
			}
		}
	}

	int getSize()      //Accesor for size of link list
	{
		return size;
	}

	T getValue(int index)      //Accesor for getting data at certain index of the list
	{
		if (size == 0) //Incase the list is empty
		{
			cout << "THE LIST IS EMPTY!" << endl;   //Prompt for user
			return NULL;
		}
		else if (index < 0 || index >= size) //Incase the passed index is out of bound
		{
			cout << "INVALID ARGUMENT!" << endl;    //Prompt for user
			return NULL;
		}
		else  //for valid situation: return data
		{
			node<T>* temp = new node<T>();    //temporary node creation
			temp = head;                      //initializing the temporary node with head
			for (int i = 0; i < index; i++)   //traverse the list until desired node is reached
			{
				temp = temp->next;
			}
			return temp->data;       //return data on the desired node
		}
	}

	node <T>* getHead()
	{
		return head;
	}

	T operator[](const int index)
	{
		node <T>* ptr = head;
		int i = 0;
		while (ptr != NULL)     // iterate till list is not empty
		{
			if (i == index)
				break;
			i++;
			ptr = ptr->next;    // update traversal node with succeeding node in each iteration
		}
		return ptr->data;
	}

	void display()   // function to display the list
	{
		node <T>* ptr = head;
		while (ptr != NULL)     // iterate till list is not empty
		{
			cout << ptr->data << " ";
			ptr = ptr->next;    // update traversal node with succeeding node in each iteration
		}
	}
};


//templatized queue 
template<typename T>
struct QueueNode
{
	//Data Members
	T data;
	QueueNode<T>* next;

	//Member Functions

	QueueNode()   //Default Construuctor
	{
		next = NULL;
	}
};

template <typename T>
class Queue
{
	//Data Members
	QueueNode<T>* front;
	QueueNode<T>* back;

public:

	//Member Functions

	Queue()    //Default Constructor
	{
		front = back = NULL;
	}

	bool IsEmpty()    //Returns true if the Queue is empty
	{
		if (front == NULL && back == NULL)
			return true;
		return false;
	}

	QueueNode<T>* getFront()   //Accessor for getting front of queue
	{
		return front;
	}

	void Enqueue(T newData)   //function to add nodes to the queue
	{
		QueueNode<T>* temp = new QueueNode<T>();    // Temporary node creation
		temp->data = newData;                       // Initializing data of temp with the passed parameter
		temp->next = NULL;                          // Setting next to Null for temp

		if (front == NULL && back == NULL)     //In case the list is empty
		{
			front = back = temp;
		}
		else       //In case the list is not empty
		{
			back->next = temp;    //adding node from the back of the queue
			back = temp;
		}
	}

	void Dequeue()
	{
		if (front == NULL && back == NULL)    //In case the queue is empty
		{
			cout << "QUEUE IS EMPTY!" << endl;   //Prompt for user
		}
		else
		{
			QueueNode<T>* temp = front;   // Temporary node creation & initialization with front of queue
			front = front->next;          // update front with succeeding node

			if (front == NULL)            // If last node is reached the update back with NULL too
			{
				back = NULL;
			}

			delete temp;				  // delete the front 
		}
	}

	~Queue()   //Destructor for queue
	{
		while (front != NULL)    //iterates till front is not empty
		{
			QueueNode<T>* temp = front;   //set a temp node equal to front
			front = front->next;   //update front with succeeding node
			delete temp;          //deleting temp node for clearing the queue
		}
	}
};

template  <typename T>
class Graph
{
	//Data Members
	LinkList <T> Vertices;
	int TotalVertices;
	LinkList <T>* adjList;

public:

	//Member Functions

	Graph()      //Default Constructor
	{
		TotalVertices = 0;
	}

	void LoadData(string filePath)
	{
		ifstream read;	// Creating object for file reading

		read.open(filePath);	// Opening file

		if (!read)   //If file doesnot open-up 
		{
			cout << "ERROR! UNABLE TO OPEN THE FILE." << endl;  //prompt for user
			return;
		}
		else    // If file open-ups
		{
			string input = " ";    //for taking input of each line as a single string
			T temp_read;      // varaible for tempoaray data storage

			getline(read, input);
			getline(read, input);
			getline(read, input);
			getline(read, input);

			while (!read.eof())    // read file till end is not reached
			{
				read >> temp_read;     // read data into temporary variable
				Vertices.addingnodeinEND(temp_read);  // add the read data to the link list
			}

			read.close();    //closing file after data extraction

			TotalVertices = Vertices.getSize();   // updating total vertices

			adjList = new LinkList <T>[TotalVertices];   // creating adjacency list 

			read.open(filePath);	// Opening file again to populate adjacenecy list

			if (!read)   //If file doesnot open-up 
			{
				cout << "ERROR! UNABLE TO OPEN THE FILE." << endl;  //prompt for user
				return;
			}
			else    // If file open-ups
			{
				input = " ";    //for taking input of each line as a single string
				int current_vertex;    //

				getline(read, input);
				getline(read, input);
				getline(read, input);
				getline(read, input);

				while (getline(read, input)) //reads aentire file one by one into a string
				{
					char* input_arr = new char[input.length() + 1];    //creating character array to store the input string
					strcpy_s(input_arr, input.length() + 1, input.c_str());      //copying the input string to the character array
					string temp_str = " ";      // for temporary storage of each token
					char* nextToken = NULL;    // stores pointer to next token

					char delim[] = "\t";        //setting the delimiter to space for character array tokenization
					char* token = strtok_s(input_arr, delim, &nextToken);      // setting the pointer to +1 index of first occurence of delimiter

					temp_str = token;           //storing the first token to string
					current_vertex = stoi(temp_str);    // converts the read first token to string
					int index_track = NULL;            // to keep track of index for storing edges for later
					node <T>* temp_vertex = Vertices.getHead();      // temporaynode to iterate through the vertices list

					for (int i = 0; i < TotalVertices; i++)   // loop iterates through all nodes of the list
					{
						if (temp_vertex->data == current_vertex)  // in case data on a the list matches the currently read vertex from file
						{
							index_track = i;     // store the index and break the loop
							break;
						}
						temp_vertex = temp_vertex->next;      //update the temporary node with succeeding node in each iteration
					}

					/*while (token = strtok_s(NULL, delim, &nextToken))
					{
						temp_str = token;           //storing the first token to string
						current_vertex = stoi(temp_str);

						adjList[index_track].addingnodeinEND(current_vertex);
					}*/

					bool space_check = false;  // flag to keep check of spaces in the string read from the file
					string edge_str;

					for (int i = 0; input[i] != '\0'; i++)    // till the read string is not null
					{
						if (input[i] == '	' || input[i] == '\t')  // if any space is observed in the string
						{
							space_check = true;   // set the flag to true
						}
						else if (space_check != false)   // in case the flag is true then concatenate the remaining string into edge variable
						{
							edge_str += input[i];   //concatenating
						}
					}

					if (!edge_str.empty())   // in case concatenated string is not empty
					{
						int edge_int;    // create an int variable to store the converted string
						edge_int = stoi(edge_str);   // convert concatenated string to integer
						adjList[index_track].addingnodeinEND(edge_int);   //update the adjacenecy list's matched index with required vertex and set it to the edges of that vertex
					}
				}
			}
		}

		/* node<T> temp1 = Vertices.getHead();

		for (int i = 0; i < TotalVertices; i++)
		{
			cout << "=>" << temp1->data << endl;
			adjList[i].display();
			cout << endl;
			temp1 = temp1->next;
		}*/
	}

	int getTotalVertices()   // function to get the total vertices 
	{
		return TotalVertices;
	}

	int getTotalEdges()  // function to get total edges in the adjacency list
	{
		int total_edges = 0;
		for (int i = 0; i < TotalVertices; i++)
		{
			total_edges += adjList[i].getSize();   // adds up all the edges by getting size of each link list in the array in each iteration
		}
		return total_edges;
	}

	void displayVertices()    // function to display the list of vertices
	{
		Vertices.display();
	}

	int getSinkNodes()   // function to return sink nodes of the graph
	{
		bool neighbour_check = false;   // flag check to detect neigbours of each vertex
		int count = 0;       // count check to maintain total sink nodes

		for (int i = 0; i < TotalVertices; i++)    // loop iterates till the adjacency lists of each vertex is visited one by one
		{
			neighbour_check = false;    // reset flag in each iteration

			if (adjList[i].getSize() != 0)     // if size of adjacency list is not zero then it means vertex has neighbours
			{
				neighbour_check = true;    // set neighbour flag to true if condition is true
			}

			if (neighbour_check == false)   // in case no neighbour is found then vertex is a sink node
			{
				count++;   // incrementing count if condition is true
			}
		}
		return count;   // return the total number of of sink nodes
	}

	int getSourceNodes() // function to return sourxe nodes of the graph
	{
		node <T>* currentNode = Vertices.getHead();   // temporary node creation to iterate through vertices link list
		bool neighbour_check = false;    // flag check to detect neigbours of each vertex
		int count = 0;                   // count check to maintain total source nodes

		for (int i = 0; i < TotalVertices; i++)  // loop iterates till all the vertices are visited one by one
		{
			neighbour_check = false;   // reset flag in each iteration
			for (int j = 0; j < TotalVertices; j++)      // loop iterates till the adjacency lists of each vertex is visited one by one
			{
				node <T>* temp_edge = adjList[j].getHead();  // stores the head of list on jth index

				for (int k = 0; k < adjList[j].getSize(); k++)   // loop iterates till all nodes are visited in the list on jth index 
				{
					if (temp_edge->data == currentNode->data)    // in case the vertex is present in adjacency list of any other vertex then its is not a source node
					{
						neighbour_check = true;     // set neighbour flag to true if condition is true
						break;   // break from the loop
					}

					if (neighbour_check == true)   // if current vertex was found as a neighbour in the adjacency list
						break;   // break from the loop

					temp_edge = temp_edge->next;   // update the temp iterator with succeeding node for list on jth index
				}
			}

			if (neighbour_check == false)  // in case the vertex is not found in any og the neighbours of other vertex then it is a source vertex
			{
				count++;    // incrementing count if condition is true
			}

			currentNode = currentNode->next;   // update current node with succeeding node for vertices list
		}

		return count;   // return the total number of source nodes
	}

	int getIsolatedNodes()
	{
		int count = 0;                    // count check to maintain total isolated nodes
		bool neighbour_check1 = false;    // flag check to detect neigbours of each vertex while checking sink nodes
		bool neighbour_check2 = false;    // flag check to detect neigbours of each vertex while checking source nodes
		bool source_check = false;        // flag check to detect if vertex is source or not
		bool sink_check = false;          // flag check to detect if vertex is sink or not
		node <T>* currentNode = Vertices.getHead();   // temporary node creation to iterate through vertices link list

		for (int i = 0; i < TotalVertices; i++)  // loop iterates till all the vertices are visited one by one
		{
			neighbour_check1 = false;    // reset flags in each iteration
			sink_check = false;

			if (adjList[i].getSize() != 0)    // if size of adjacency list is not zero then it means vertex has neighbours
			{
				neighbour_check1 = true;      // set neighbour flag to true if condition is true
			}

			if (neighbour_check1 == false)    // in case no neighbour is found then vertex is a sink node
			{
				sink_check = true;           // set sink node flag to true
			}

			neighbour_check2 = false;    // reset flags in each iteration
			source_check = false;

			for (int j = 0; j < TotalVertices; j++)    // loop iterates till the adjacency lists of each vertex is visited one by one
			{
				node <T>* temp_edge = adjList[j].getHead();   // stores the head of list on jth index

				for (int k = 0; k < adjList[j].getSize(); k++)   // loop iterates till all nodes are visited in the list on jth index 
				{
					if (temp_edge->data == currentNode->data)   // in case the vertex is present in adjacency list of any other vertex then its is not a source node
					{
						neighbour_check2 = true;      // set neighbour flag to true if condition is true
						break;                       // break from the loop
					}


					temp_edge = temp_edge->next;   // update the temp iterator with succeeding node for list on jth index
				}
				if (neighbour_check2 == true)     // if current vertex was found as a neighbour in the adjacency list
					break;                       // break from the loop
			}

			if (neighbour_check2 == false)   // in case the vertex is not found in any og the neighbours of other vertex then it is a source vertex
			{
				source_check = true;         // set source node flag to true
			}

			if (sink_check == true && source_check == true)  // in case a node satisfies to be both sink and source then it is isolated node
			{
				count++;    // incrementing count if condition is true
			}

			currentNode = currentNode->next;      // update current node with succeeding node for vertices list
		}
		return count;    // return total number of isolated nodes
	}

	T* BFS(int currentNode)
	{
		bool* visited = new bool[TotalVertices];     // boolean type array to keep track of visited nodes

		for (int i = 0; i < TotalVertices; i++)       // setting the entire array to false initially
			visited[i] = false;

		int startVertex = 0;        // varaible for starting vertex

		for (int i = 0; i < TotalVertices; i++)      // loop iterates till the size of vertices link list
		{
			if (Vertices[i] == currentNode)    // in case the vertex node matches the passed current node then set that index of vertices link list to starting vertex
			{
				startVertex = i; // set that index of vertices link list to starting vertex if the condition is true
				break;    // break from the loop if condition is full filled
			}
		}

		Queue<int> q; // creating an instance of queue class 

		visited[startVertex] = true;  // starting with the start vertex and marking it as visited

		q.Enqueue(startVertex);     // enque the start veres in the queue

		int size = TotalVertices;   // setting size of reachable array to number of total arrya

		T* reachable = new T[size];      // an array to store values of nodes of the graph 

		while (!q.IsEmpty())     // loop iterates till the visited vertices queue is not empty
		{
			startVertex = q.getFront()->data;     // update the start vertex with new front in each iteration

			for (int i = 0; i < size; i++)       //  loop iterated for set size
			{
				reachable[i] = Vertices[startVertex];    // update reachable in each iteration
			}

			q.Dequeue();    // dequeue the front from the queue

			node<T>* temp = adjList[startVertex].getHead();     // temp node to store the head of list stored on start index

			while (temp != nullptr)         // till the the list is not null
			{
				for (int i = 0; i < TotalVertices; i++)     // iterates till size of vertices link list
				{
					if (temp->data == Vertices[i])     // in case data on list matched the vertex in current iteration 
					{
						if (!visited[i])
						{
							q.Enqueue(i);            // enqueue the index value in the queue
							visited[i] = true;      // set the current index of visited to true
						}
					}
				}
				temp = temp->next;   // update temp node with succeeding node in each iteration
			}
		}
		return reachable;      // return the pointer to reachable array 
	}

	void shortestPathDistribution(int start, int end) {
		int size = (end - start) + 1;					//Calculating size from given range
		int* lengths = new int[size];					//Lengths array of size given range
		int* distributions = new int[size];				//Contains number of paths of current length
		int* distances = new int[Vertices.getSize()];		//To keep distances of specific vertex with all other

		//shortestDistance(2, distances);
		//return;

		//Initializing lengths array
		for (int i = 0; i < size; i++) {
			lengths[i] = start++;
			distributions[i] = 0;
		}

		for (int i = 0; i < 1; i++)
		{
			// Getting distances of current vertex from all other
			//cout << vertices;
			shortestDistance(Vertices[i], distances);

			// Setting number of paths lengths accordingly
			for (int j = 0; j < Vertices.getSize(); j++)
			{
				for (int k = 0; k < size; k++)
				{
					if (distances[j] == lengths[k])
					{
						distributions[k]++;
					}
				}
			}
		}

		for (int i = 0; i < size; i++)
		{
			cout << "Paths of length " << lengths[i] << ": " << distributions[i] << endl;
		}
	}

	void shortestDistance(T startVertex, int* distances)
	{
		bool vertFound = false;
		bool* visited = new bool[Vertices.getSize()];
		for (int i = 0; i < Vertices.getSize(); i++)
		{
			visited[i] = false;
			distances[i] = -1;
		}

		Queue<int> q;
		int ind;
		for (int i = 0; i < Vertices.getSize(); i++)
		{
			if (Vertices[i] == startVertex)
			{
				ind = i;
				break;
			}
		}
		visited[ind] = true;
		distances[ind] = 0;

		q.Enqueue(startVertex);

		while (!q.IsEmpty())
		{
			startVertex = q.getFront()->data;

			q.Dequeue();
			for (int i = 0; i < Vertices.getSize(); i++)
			{
				if (Vertices[i] == startVertex)
				{
					ind = i;
					break;
				}
			}
			node<T>* temp = adjList[ind].getHead();

			while (temp != nullptr)
			{

				for (int i = 0; i < Vertices.getSize(); i++) {

					if (temp->data == Vertices[i]) {

						if (!visited[i]) {
							q.Enqueue(Vertices[i]);
							visited[i] = true;
							distances[i] = distances[ind] + 1;
						}
					}
				}

				temp = temp->next;
			}
		}
	}

	void getInDegree() {

		cout << endl;
		for (int i = 0; i < TotalVertices; i++)
		{
			int count = 0;
			for (int j = 0; j < TotalVertices; j++)
			{
				for (int k = 0; k < adjList[j].getSize(); k++)
				{
					if (Vertices[i] == adjList[j][k])
					{
						count++;
					}
				}
			}
			cout << "In degree of " << Vertices[i] << " : " << ((float)count) / TotalVertices << endl;
		}
	}

	void getOutDegree() {

		for (int i = 0; i < TotalVertices; i++)
		{
			cout << "Out degree of " << Vertices[i] << " : " << ((float)adjList[i].getSize()) / TotalVertices << endl;
		}

	}

	T* IN_ALGO(int sourceVertex)
	{
		T* IN = new T[TotalVertices];
		T* BFS_arr = new T[TotalVertices];
		node <T>* currentVertex = Vertices.getHead();

		for (int i = 0, j = 0; i < TotalVertices; i++)
		{
			BFS_arr = BFS(currentVertex->data);
			for (int k = 0; k < TotalVertices; k++)
			{
				if (sourceVertex == BFS_arr[k])
				{
					IN[j] = currentVertex->data;
					j++;
				}
			}
			currentVertex = currentVertex->next;
		}
		return IN;
	}

	T* OUT_ALGO(int sourceVertex)
	{
		T* OUT = new T[TotalVertices];
		OUT = BFS(sourceVertex);
		return OUT;
	}

	T* UNIQUE(T* arr)
	{
		T* uniqueARR = new T[TotalVertices];
		bool repetition_flag = false;

		for (int i = 0, j = 0; i < TotalVertices; i++)
		{
			repetition_flag = false;
			for (int k = 0; k < TotalVertices; k++)
			{
				if (uniqueARR[k] = arr[i])
				{
					repetition_flag = true;
				}
			}

			if (repetition_flag == false)
			{
				uniqueARR[j] = arr[i];
				j++;
			}
		}
		return uniqueARR;
	}

	T* SCC()
	{
		T* SCC_arr = new T[TotalVertices];
		T* IN_arr = new T[TotalVertices];
		T* OUT_arr = new T[TotalVertices];
		node <T>* currentVertex = Vertices.getHead();
		bool IN_flag = false;
		bool OUT_flag = false;

		for (int i = 0, k = 0; i < TotalVertices; i++)
		{
			IN_arr = IN_ALGO(currentVertex->data);
			OUT_arr = OUT_ALGO(currentVertex->data);
			IN_flag = false;
			OUT_flag = false;

			for (int j = 0; j < TotalVertices; j++)
			{
				if (currentVertex->data == IN_arr[j])
				{
					IN_flag = true;
				}
				if (currentVertex->data == OUT_arr[j])
				{
					OUT_flag = true;
				}
				if (IN_flag == true && OUT_flag == true)
				{
					break;
				}

			}

			if (IN_flag == true && OUT_flag == true)
			{
				SCC_arr[k] = currentVertex->data;
				cout << SCC_arr[k] << endl;
				k++;
			}

			currentVertex = currentVertex->next;
		}
		return UNIQUE(SCC_arr);
	}

	T* WCC() {

		T* WCC_arr = new T[TotalVertices];

		node <T>* currentVertex = Vertices.getHead();

		for (int i = 0; i < TotalVertices; i++)
		{
			WCC_arr[i] = BFS(currentVertex->data);

			currentVertex = currentVertex->next;
		}

		return UNIQUE(WCC_arr);
	}

};



//Driver Function
int main()
{
	Graph <int> g1;
	int userChoice = -1;
	int exitFlag = -1;
	//g1.LoadData("trytext.txt");
	g1.LoadData("CA-GrQc.txt");
	//g1.SCC();
	/*for (int i = 0; ptr != NULL; i++)
	{
		cout << ptr[i] << endl;
	}*/

	/*//cout << "EDGES: " << g1.getTotalEdges() << endl;
	//cout << "VERTICES: "<<g1.getTotalVertices()<<endl;
	//cout << g1.getSinkNodes() << endl;
	//cout << g1.getSourceNodes() << endl;
	//cout << "==>" << g1.getIsolatedNodes() << endl;*/
	//g1.BFS(1);
	//g1.shortestPathDistribution(1,2);

	do
	{
		cout << "***************************************************************************" << endl
			<< "                       NETWORK ANALYSIS USING GRAPH                        " << endl
			<< "***************************************************************************" << endl;

		cout << "THE PROGRAM OFFERS FOLLOWING FUNCTIONALITIES FOR \'CA-GrQc\' DATA SET:" << endl
			<< "1. Display the number of nodes." << endl
			<< "2. Display the number of edges." << endl
			<< "3. Display the number of source nodes." << endl
			<< "4. Display the number of sink nodes." << endl
			<< "5. Display the number of isolated nodes." << endl
			<< "6. Display the number of bridge edges." << endl
			<< "7. Display the number of articulation nodes." << endl
			<< "8. Display the shortest path length distribution." << endl
			<< "9. Display the diameter of the graph." << endl
			<< "10. Display the in - degree distribution in the form of a table." << endl
			<< "11. Display the out - degree distribution in the form of a table." << endl
			<< "12. Display the size of the largest strongly connected component(SCC)." << endl
			<< "13. Display the size distribution of all SCCs." << endl
			<< "14. Display the size of the largest weakly connected component(WCC)." << endl
			<< "15. Display the size distribution of all WCCs." << endl;

		do
		{
			cout << "ENTER YOUR CHOICE (1-15 Only) : ";
			cin >> userChoice;
			if (userChoice < 1 || userChoice > 15)
			{
				cout << "INVALID CHOICE !" << endl;
			}
		} while (userChoice < 1 || userChoice > 15);

		if (userChoice == 1)
		{
			do
			{
				cout << "\nNumber of nodes : " << g1.getTotalVertices() << endl;
				cout << "\nNOTE : ENTER \'1\' to CONTINUE OR \'0\' to EXIT." << endl;
				cout << "ENTER CHOICE (0 OR 1 ONLY) : ";
				cin >> exitFlag;
				if (exitFlag < 0 || exitFlag>1)
				{
					cout << "INVALID CHOICE !" << endl;
				}
			} while (exitFlag < 0 || exitFlag>1);
		}
		else if (userChoice == 2)
		{
			do
			{
				cout << "\n==================================" << endl;
				cout << "Number of Edges : " << g1.getTotalEdges() << endl;
				cout << "==================================" << endl;
				cout << "\nNOTE : ENTER \'1\' to CONTINUE OR \'0\' to EXIT." << endl;
				cout << "ENTER CHOICE (0 OR 1 ONLY) : ";
				cin >> exitFlag;
				if (exitFlag < 0 || exitFlag>1)
				{
					cout << "INVALID CHOICE !" << endl;
				}
			} while (exitFlag < 0 || exitFlag>1);
		}
		else if (userChoice == 3)
		{
			do
			{
				cout << "\n==================================" << endl;
				cout << "Number of Source Nodes : " << g1.getSourceNodes() << endl;
				cout << "==================================" << endl;
				cout << "NOTE : ENTER \'1\' to CONTINUE OR \'0\' to EXIT." << endl;
				cout << "ENTER CHOICE (0 OR 1 ONLY) : ";
				cin >> exitFlag;
				if (exitFlag < 0 || exitFlag>1)
				{
					cout << "INVALID CHOICE !" << endl;
				}
			} while (exitFlag < 0 || exitFlag>1);
		}
		else if (userChoice == 4)
		{
			do
			{
				cout << "\n==================================" << endl;
				cout << "Number of Sink Nodes : " << g1.getSinkNodes() << endl;
				cout << "==================================" << endl;
				cout << "NOTE : ENTER \'1\' to CONTINUE OR \'0\' to EXIT." << endl;
				cout << "ENTER CHOICE (0 OR 1 ONLY) : ";
				cin >> exitFlag;
				if (exitFlag < 0 || exitFlag>1)
				{
					cout << "INVALID CHOICE !" << endl;
				}
			} while (exitFlag < 0 || exitFlag>1);
		}
		else if (userChoice == 5)
		{
			do
			{
				cout << "\n==================================" << endl;
				cout << "Number of Isolated Nodes : " << g1.getIsolatedNodes() << endl;
				cout << "==================================" << endl;
				cout << "NOTE : ENTER \'1\' to CONTINUE OR \'0\' to EXIT." << endl;
				cout << "ENTER CHOICE (0 OR 1 ONLY) : ";
				cin >> exitFlag;
				if (exitFlag < 0 || exitFlag>1)
				{
					cout << "INVALID CHOICE !" << endl;
				}
			} while (exitFlag < 0 || exitFlag>1);
		}
		else if (userChoice == 6)
		{
			do
			{
				cout << "NOTE : ENTER \'1\' to CONTINUE OR \'0\' to EXIT." << endl;
				cout << "ENTER CHOICE (0 OR 1 ONLY) : ";
				cin >> exitFlag;
				if (exitFlag < 0 || exitFlag>1)
				{
					cout << "INVALID CHOICE !" << endl;
				}
			} while (exitFlag < 0 || exitFlag>1);
		}
		else if (userChoice == 7)
		{
			do
			{
				cout << "NOTE : ENTER \'1\' to CONTINUE OR \'0\' to EXIT." << endl;
				cout << "ENTER CHOICE (0 OR 1 ONLY) : ";
				cin >> exitFlag;
				if (exitFlag < 0 || exitFlag>1)
				{
					cout << "INVALID CHOICE !" << endl;
				}
			} while (exitFlag < 0 || exitFlag>1);
		}
		else if (userChoice == 8)
		{
			do
			{
				cout << "\n==================================" << endl;
				g1.shortestPathDistribution(1, 20);
				cout << "==================================" << endl;
				cout << "NOTE : ENTER \'1\' to CONTINUE OR \'0\' to EXIT." << endl;
				cout << "ENTER CHOICE (0 OR 1 ONLY) : ";
				cin >> exitFlag;
				if (exitFlag < 0 || exitFlag>1)
				{
					cout << "INVALID CHOICE !" << endl;
				}
			} while (exitFlag < 0 || exitFlag>1);
		}
		else if (userChoice == 9)
		{
			do
			{
				cout << "NOTE : ENTER \'1\' to CONTINUE OR \'0\' to EXIT." << endl;
				cout << "ENTER CHOICE (0 OR 1 ONLY) : ";
				cin >> exitFlag;
				if (exitFlag < 0 || exitFlag>1)
				{
					cout << "INVALID CHOICE !" << endl;
				}
			} while (exitFlag < 0 || exitFlag>1);
		}
		else if (userChoice == 10)
		{
			do
			{
				cout << "\n==================================" << endl;
				g1.getInDegree();
				cout << "==================================" << endl;
				cout << "NOTE : ENTER \'1\' to CONTINUE OR \'0\' to EXIT." << endl;
				cout << "ENTER CHOICE (0 OR 1 ONLY) : ";
				cin >> exitFlag;
				if (exitFlag < 0 || exitFlag>1)
				{
					cout << "INVALID CHOICE !" << endl;
				}
			} while (exitFlag < 0 || exitFlag>1);
		}
		else if (userChoice == 11)
		{
			do
			{
				cout << "\n==================================" << endl;
				g1.getOutDegree();
				cout << "==================================" << endl;
				cout << "NOTE : ENTER \'1\' to CONTINUE OR \'0\' to EXIT." << endl;
				cout << "ENTER CHOICE (0 OR 1 ONLY) : ";
				cin >> exitFlag;
				if (exitFlag < 0 || exitFlag>1)
				{
					cout << "INVALID CHOICE !" << endl;
				}
			} while (exitFlag < 0 || exitFlag>1);
		}
		else if (userChoice == 12)
		{
			do
			{
				cout << "NOTE : ENTER \'1\' to CONTINUE OR \'0\' to EXIT." << endl;
				cout << "ENTER CHOICE (0 OR 1 ONLY) : ";
				cin >> exitFlag;
				if (exitFlag < 0 || exitFlag>1)
				{
					cout << "INVALID CHOICE !" << endl;
				}
			} while (exitFlag < 0 || exitFlag>1);
		}
		else if (userChoice == 13)
		{
			do
			{
				cout << "NOTE : ENTER \'1\' to CONTINUE OR \'0\' to EXIT." << endl;
				cout << "ENTER CHOICE (0 OR 1 ONLY) : ";
				cin >> exitFlag;
				if (exitFlag < 0 || exitFlag>1)
				{
					cout << "INVALID CHOICE !" << endl;
				}
			} while (exitFlag < 0 || exitFlag>1);
		}
		else if (userChoice == 14)
		{
			do
			{
				cout << "NOTE : ENTER \'1\' to CONTINUE OR \'0\' to EXIT." << endl;
				cout << "ENTER CHOICE (0 OR 1 ONLY) : ";
				cin >> exitFlag;
				if (exitFlag < 0 || exitFlag>1)
				{
					cout << "INVALID CHOICE !" << endl;
				}
			} while (exitFlag < 0 || exitFlag>1);
		}
		else if (userChoice == 15)
		{
			do
			{
				cout << "NOTE : ENTER \'1\' to CONTINUE OR \'0\' to EXIT." << endl;
				cout << "ENTER CHOICE (0 OR 1 ONLY) : ";
				cin >> exitFlag;
				if (exitFlag < 0 || exitFlag>1)
				{
					cout << "INVALID CHOICE !" << endl;
				}
			} while (exitFlag < 0 || exitFlag>1);
		}

	} while (exitFlag != 0);

	return 0;
}