#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <ctime>
#include <string>
using namespace std;

const int SCREEN_WIDTH = 910;
const int SCREEN_HEIGHT = 750;

const int arrSize = 130;
const int rectSize = 7;

int arr[arrSize];
int Barr[arrSize];

bool complete = false;

void visualize(sf::RenderWindow& window, int x = -1, int y = -1, int z = -1) {
    window.clear(sf::Color::Black);

    for (int i = 0; i < arrSize; ++i) {
        sf::RectangleShape rect(sf::Vector2f(rectSize, arr[i]));
        rect.setPosition(i * rectSize, SCREEN_HEIGHT - arr[i]);

        if (complete) {
            rect.setFillColor(sf::Color(100, 180, 100));
        } else if (i == x || i == z) {
            rect.setFillColor(sf::Color(100, 180, 100));
        } else if (i == y) {
            rect.setFillColor(sf::Color(165, 105, 189));
        } else {
            rect.setFillColor(sf::Color(170, 183, 184));
        }

        window.draw(rect);
    }
    window.display();
}

void inplaceHeapSort(int* input, int n, sf::RenderWindow& window) {
    for (int i = 1; i < n; i++) {
        int childIndex = i;
        int parentIndex = (childIndex - 1) / 2;

        while (childIndex > 0) {
            if (input[childIndex] > input[parentIndex]) {
                std::swap(input[parentIndex], input[childIndex]);
            } else {
                break;
            }

            visualize(window, parentIndex, childIndex);
            sf::sleep(sf::milliseconds(40));

            childIndex = parentIndex;
            parentIndex = (childIndex - 1) / 2;
        }
    }

    for (int heapLast = n - 1; heapLast >= 0; heapLast--) {
        std::swap(input[0], input[heapLast]);

        int parentIndex = 0;
        int leftChildIndex = 2 * parentIndex + 1;
        int rightChildIndex = 2 * parentIndex + 2;

        while (leftChildIndex < heapLast) {
            int maxIndex = parentIndex;

            if (input[leftChildIndex] > input[maxIndex]) {
                maxIndex = leftChildIndex;
            }
            if (rightChildIndex < heapLast && input[rightChildIndex] > input[maxIndex]) {
                maxIndex = rightChildIndex;
            }
            if (maxIndex == parentIndex) {
                break;
            }

            std::swap(input[parentIndex], input[maxIndex]);
            visualize(window, maxIndex, parentIndex, heapLast);
            sf::sleep(sf::milliseconds(40));

            parentIndex = maxIndex;
            leftChildIndex = 2 * parentIndex + 1;
            rightChildIndex = 2 * parentIndex + 2;
        }
    }
}

int partition_array(int a[], int si, int ei, sf::RenderWindow& window) {
    int count_small = 0;

    for (int i = (si + 1); i <= ei; i++) {
        if (a[i] <= a[si]) {
            count_small++;
        }
    }
    int c = si + count_small;
    std::swap(a[c], a[si]);
    visualize(window, c, si);

    int i = si, j = ei;

    while (i < c && j > c) {
        if (a[i] <= a[c]) {
            i++;
        } else if (a[j] > a[c]) {
            j--;
        } else {
            std::swap(a[j], a[i]);

            visualize(window, i, j);
            sf::sleep(sf::milliseconds(70));

            i++;
            j--;
        }
    }
    return c;
}

void quickSort(int a[], int si, int ei, sf::RenderWindow& window) {
    if (si >= ei) {
        return;
    }

    int c = partition_array(a, si, ei, window);
    quickSort(a, si, c - 1, window);
    quickSort(a, c + 1, ei, window);
}

void merge2SortedArrays(int a[], int si, int ei, sf::RenderWindow& window) {
    int size_output = (ei - si) + 1;
    int* output = new int[size_output];

    int mid = (si + ei) / 2;
    int i = si, j = mid + 1, k = 0;
    while (i <= mid && j <= ei) {
        if (a[i] <= a[j]) {
            output[k] = a[i];
            visualize(window, i, j);
            i++;
            k++;
        } else {
            output[k] = a[j];
            visualize(window, i, j);
            j++;
            k++;
        }
    }
    while (i <= mid) {
        output[k] = a[i];
        visualize(window, -1, i);
        i++;
        k++;
    }
    while (j <= ei) {
        output[k] = a[j];
        visualize(window, -1, j);
        j++;
        k++;
    }
    int x = 0;
    for (int l = si; l <= ei; l++) {
        a[l] = output[x];
        visualize(window, l);
        sf::sleep(sf::milliseconds(15));
        x++;
    }
    delete[] output;
}

void mergeSort(int a[], int si, int ei, sf::RenderWindow& window) {
    if (si >= ei) {
        return;
    }
    int mid = (si + ei) / 2;

    mergeSort(a, si, mid, window);
    mergeSort(a, mid + 1, ei, window);

    merge2SortedArrays(a, si, ei, window);
}

void bubbleSort(sf::RenderWindow& window) {
    for (int i = 0; i < arrSize - 1; i++) {
        for (int j = 0; j < arrSize - 1 - i; j++) {
            if (arr[j + 1] < arr[j]) {
                std::swap(arr[j], arr[j + 1]);

                visualize(window, j + 1, j, arrSize - i);
            }
            sf::sleep(sf::milliseconds(1));
        }
    }
}

void insertionSort(sf::RenderWindow& window) {
    for (int i = 1; i < arrSize; i++) {
        int j = i - 1;
        int temp = arr[i];
        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;

            visualize(window, i, j + 1);
            sf::sleep(sf::milliseconds(5));
        }
        arr[j + 1] = temp;
    }
}

void selectionSort(sf::RenderWindow& window) {
    int minIndex;
    for (int i = 0; i < arrSize - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < arrSize; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
                visualize(window, i, minIndex);
            }
            sf::sleep(sf::milliseconds(1));
        }
        std::swap(arr[i], arr[minIndex]);
    }
}

void loadArr() {
    memcpy(arr, Barr, sizeof(int) * arrSize);
}

void randomizeAndSaveArray() {
    unsigned int seed = static_cast<unsigned int>(time(NULL));
    srand(seed);
    for (int i = 0; i < arrSize; i++) {
        int random = rand() % SCREEN_HEIGHT;
        Barr[i] = random;
    }
}

void execute(sf::RenderWindow& window) {
    randomizeAndSaveArray();
    loadArr();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                complete = false;
            }
            else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Q:
                        window.close();
                        complete = false;
                        cout << "\nEXITING SORTING VISUALIZER.\n";
                        break;
                    case sf::Keyboard::Num0:
                        randomizeAndSaveArray();
                        complete = false;
                        loadArr();
                        cout << "\nNEW RANDOM LIST GENERATED.\n";
                        break;
                    case sf::Keyboard::Num1:
                        loadArr();
                        cout << "\nSELECTION SORT STARTED.\n";
                        complete = false;
                        selectionSort(window);
                        complete = true;
                        cout << "\nSELECTION SORT COMPLETE.\n";
                        break;
                    case sf::Keyboard::Num2:
                        loadArr();
                        cout << "\nINSERTION SORT STARTED.\n";
                        complete = false;
                        insertionSort(window);
                        complete = true;
                        cout << "\nINSERTION SORT COMPLETE.\n";
                        break;
                    case sf::Keyboard::Num3:
                        loadArr();
                        cout << "\nBUBBLE SORT STARTED.\n";
                        complete = false;
                        bubbleSort(window);
                        complete = true;
                        cout << "\nBUBBLE SORT COMPLETE.\n";
                        break;
                    case sf::Keyboard::Num4:
                        loadArr();
                        cout << "\nMERGE SORT STARTED.\n";
                        complete = false;
                        mergeSort(arr, 0, arrSize - 1, window);
                        complete = true;
                        cout << "\nMERGE SORT COMPLETE.\n";
                        break;
                    case sf::Keyboard::Num5:
                        loadArr();
                        cout << "\nQUICK SORT STARTED.\n";
                        complete = false;
                        quickSort(arr, 0, arrSize - 1, window);
                        complete = true;
                        cout << "\nQUICK SORT COMPLETE.\n";
                        break;
                    case sf::Keyboard::Num6:
                        loadArr();
                        cout << "\nHEAP SORT STARTED.\n";
                        complete = false;
                        inplaceHeapSort(arr, arrSize, window);
                        complete = true;
                        cout << "\nHEAP SORT COMPLETE.\n";
                        break;
                }
            }
        }
        visualize(window);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Sorting Visualizer");

    cout << "__________________________________________________" << endl;
    cout << "\n                    SORTING VISUALIZER            " << endl;
    cout << "__________________________________________________" << endl;

    cout << "\nPress 0 to generate a new random list." << endl;
    cout << "Press 1 to Selection Sort." << endl;
    cout << "Press 2 to Insertion Sort." << endl;
    cout << "Press 3 to Bubble Sort." << endl;
    cout << "Press 4 to Merge Sort." << endl;
    cout << "Press 5 to Quick Sort." << endl;
    cout << "Press 6 to Heap Sort." << endl;
    cout << "Press Q to quit the visualizer." << endl;

    execute(window);
    return 0;
}
