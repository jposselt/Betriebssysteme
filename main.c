#include <stdio.h>
#include "lists.h"


// Node
typedef struct processNode {
	//Zeigt auf den nächsten Knoten
	LIST_NODE_HEADER(struct processNode);
	char name[100];
	float time;
	int priority;
} processNode;

//List
typedef struct {
	//Zeigt auf den ersten Knoten
	LIST_HEADER(processNode);
} processList;

//Erstellt neunen Knoten und fügt ihn der Liste hinzu
void addProcess(processList *list, char name[100], int time, int prio) {
	processNode *node = LIST_NEW_NODE(node);
	strcpy(node->name, name);
	node->time = time;
	node->priority = prio;
	List_append(&*list, node);
}

//Vergleicht zwei Knoten mit ihrerer Priorität
int compareProcessByPrio(processNode *process1, processNode *process2, void *dummy) {
	int cmp = process1->priority - process2->priority;
	if (cmp == 0)
		return 0;
	//Wenn Prozess1 kleiner als Prozess2 ist, steht Prozess2 vorne
	else if (cmp < 0)
		return -1;
	else
		return 1;
}
//Vergleicht zwei Knoten mit ihrere Prozesszeit
int compareProcessByTime(processNode *process1, processNode *process2, void *dummy) {
	float cmp = process1->time - process2->time;
	if (cmp == 0)
		return 0;
	//Wenn Prozess1 kleiner als Prozess2 ist, steht Prozess1 vorne
	else if (cmp < 0)
		return 1;
	else
		return -1;
}
//Vergleicht zwie Knoten mit ihrer Zeit/Priorität
int compareProcessByTimeAndPrio(processNode *process1, processNode *process2, void *dummy) {
	float cmp = (process1->time / process1->priority) - (process2->time / process2->priority);
	if (cmp == 0)
		return 0;
	//Wenn Prozess1 kleiner als Prozess2 ist, steht Prozess2 vorne
	else if (cmp < 0)
		return -1;
	else
		return 1;
}


void firstComeFirstServed(processList *list) {
	processNode *node = list->head;
	float totalTime = 0;
	while (!List_isEmpty(list)) {
	while (node != NULL) {


		totalTime += node->time;
		//Simulation des abarbeitens    
		node->time -= node->time;
		printf(" Prozess %s wurde abgearbeitet, Aktuelle Zeit: %.3f s \n", node->name, totalTime)
			node = node->next;
	}
	List_remove(list, node);
}
	float timeAverage = timeTotal / list->count;
	printf(" Mittlere Verweilzeit: %.3f s\n", timeAverage);
}

void shortesJobFirst(processList *list) {
	//Sortiere nach Zeit
	List_sort(&*list, (ListNodeCompareFunction)compareProcessByTime, NULL);
	firstComeFirstServed(list);
}

void prioritySchedule(processList *list) {
	//Sortiere nach Priorität
	List_sort(&*list, (ListNodeCompareFunction)compareProcessByPrio, NULL);
	firstComeFirstServed(list);
}

void constantRoundRobin(processList *list) {
	//Für später
	int count = list->count;
	//Gesamtarbeitszeit    
	float totalTime = 0;

	//Sortieren nach Zeit
	List_sort(&*list, (ListNodeCompareFunction)compareProcessByTime, NULL);
	processNode *node;
	while (!List_isEmpty(list) {
		node = list->head;
		if (node->time > 0) {
			//Die Zeit die abgezogen wird
			float timeToSpent = node->time;

			printf(" Es wird an den Prozessen zu folgenden Anteilen gearbeitet:\n");
			while (node != NULL) {
				printf("  Es wurde %.3fs an %s gearbeitet.\n", timeToSpent, node->name);
				node->time -= timeToSpent;
				totalTime += timeToSpent;
				if (node->time <= 0) {
					printf("%s wurde abgearbeitet.\n", node->name);
				}
				node = node->next;
			}
		}
		//Löschen eines abgearbeiteten Knoten
		List_remove(list, list->head);
	}
	float averageTime = totalTime / count;
	printf(" Mittlere Verweilzeit: %.3f s\n", averageTime);
}

void priorityRoundRobin(processList *list) {
	//Für Später
	int count = list->count;
	float totalTime = 0;
	//Sortieren nach Zeit/Priorität
	List_sort(&*list, (ListNodeCompareFunction)compareProcessByTimeAndPrio, NULL);
	processNode *node;


	while (!List_isEmpty(list)) {
		node = list->head;
		if (node->time > 0) {
			//Wie oft muss der schnellste Prozess ausgeführt werden um abgearbeitet zu werden
			float timeToSpent = node->time / node->priority


				printf(" Es wird an den Prozessen zu folgenden Anteilen gearbeitet:\n");
			while (node != NULL) {
				//Die tatsächliche Arbeitszeit 
				float timeSpent = timeToSpent * node->priority;
				printf("  Es wurde %.3fs an %s gearbeitet.\n", timeSpent, node->name);
				node->time -= timeSpent;
				totalTime += timeSpent;
				if (node->time <= 0) {
					printf("%s wurde abgearbeitet.\n", node->name);
				}
				node = node->next;
			}
		}
		List_remove(list, node);
	}
	float averageTime = totalTime / count;
	printf(" Mittlere Verweilzeit: %.3f s\n", averageTime);
}

int main() {
	processList list;
	List_init(&list);

	addProcess(&list, "A", 30, 2);
	addProcess(&list, "B", 20, 1);
	addProcess(&list, "C", 35, 5);
	addProcess(&list, "D", 28, 4);
	addProcess(&list, "E", 18, 3);

	printf("\nFirst Come First Served:\n");
	firstComeFirstServed(&list);

	addProcess(&list, "A", 30, 2);
	addProcess(&list, "B", 20, 1);
	addProcess(&list, "C", 35, 5);
	addProcess(&list, "D", 28, 4);
	addProcess(&list, "E", 18, 3);

	printf("\nShortest Job First:\n");
	shortestJobFirst(&list);

	addProcess(&list, "A", 30, 2);
	addProcess(&list, "B", 20, 1);
	addProcess(&list, "C", 35, 5);
	addProcess(&list, "D", 28, 4);
	addProcess(&list, "E", 18, 3);


	printf("\nPrioritäten gesteuert:\n");
	prioritySchedule(&list);

	addProcess(&list, "A", 30, 2);
	addProcess(&list, "B", 20, 1);
	addProcess(&list, "C", 35, 5);
	addProcess(&list, "D", 28, 4);
	addProcess(&list, "E", 18, 3);

	printf("\n Konstanter Round Robin:\n");
	constantRoundRobin(&list);

	addProcess(&list, "A", 30, 2);
	addProcess(&list, "B", 20, 1);
	addProcess(&list, "C", 35, 5);
	addProcess(&list, "D", 28, 4);
	addProcess(&list, "E", 18, 3);

	printf("\n Prioritäten Round Robin:\n");
	priorityRoundRobin(&list);

	return 0;
}
