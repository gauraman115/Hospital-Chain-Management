#include <bits/stdc++.h>
#include <vector>
#include <windows.h>
// #include <stdlib.h>
#include <unistd.h>
// #include<iostream>
using namespace std;
int s_c = -1;
int s_s = -1;

void ClearScreen()
{
  int n;
  for (n = 0; n < 10; n++)
    printf("\n");
}

// inrto page

void intro()
{

  system("cls");
  cout << "                            *************" << endl;
  cout << "                               HOSPITAL CHAIN MANAGEMENT SYSTEM" << endl;
  cout << "                            *************" << endl;
  cout << endl;
  cout << "                               Group Memmbers are:" << endl
       << endl;
  ;
  cout << "                               20103052    Aaryan Nehra " << endl;
  cout << "                               20103054    Tanishk Agarwal " << endl;
  cout << "                               20103036    Aman Gaur " << endl;
  cout << "                               20103055    Akul Goel " << endl;
  Sleep(1000);
  system("cls");
}

// structure of health checkup with its benefit & price which can user can avail

struct health_checkups
{
  string name;
  int price;
  int benefit;
};

// structure of hospital for storing hospital information

struct hospital
{
  string name;
  float rating;
  int speciality;
  int city;
  int reg_no;
};

// structure of patient for storing patient details

struct patient
{
  string name;
  int age;
  string city;
  string speciality;
};

// structue of city

struct city
{
  string city_name;
  int city_no;
  bool hospital;
};

// structure of speciality of hospitals

struct speciality
{
  string s_name;
  int s_no;
};

// graph coloring algorithm for assigning different hospitals to diff city

bool isafe(vector<vector<int>> graph, int v, int c, int colour[], int n)
{
  for (int i = 0; i < n; i++)
  {

    if (graph[v][i] != 0 && colour[i] == c)
    {
      return false;
    }
  }

  return true;
}

bool colouring(vector<vector<int>> graph, int n, int v, int colour[], int m, vector<city> ch)
{
  if (v == n)
  {
    return true;
  }

  for (int c = 1; c <= m; c++)
  {
    if (isafe(graph, v, c, colour, n))
    {
      colour[v] = c;
      if (ch[v].hospital == false)
      {
        colour[v] = 0;
      }
      if (colouring(graph, n, v + 1, colour, m, ch))
      {
        return true;
      }
      colour[v] = 0;
      return false;
    }
  }

  return false;
}

// dijkstra algorithm to finding closest hospital to patient

int minDistance(int dist[], bool sptSet[], int V)
{
  int min = INT_MAX, min_index;

  for (int v = 0; v < V; v++)
    if (sptSet[v] == false && dist[v] <= min)
    {
      min = dist[v], min_index = v;
    }

  return min_index;
}

void printSolution(int dist[], int V)
{
  cout << "Vertex \t Distance from Source" << endl;

  for (int i = 0; i < V; i++)
  {
    cout << i << " \t\t" << dist[i] << endl;
  }
}

void dijkstra(vector<vector<int>> graph, int src, int V, int dist[])
{
  bool sptSet[V];
  for (int i = 0; i < V; i++)
  {
    dist[i] = INT_MAX, sptSet[i] = false;
  }
  dist[src] = 0;
  for (int count = 0; count < V - 1; count++)
  {
    int u = minDistance(dist, sptSet, V);
    sptSet[u] = true;
    for (int v = 0; v < V; v++)
    {
      if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
      {
        dist[v] = dist[u] + graph[u][v];
      }
    }
  }
  // printSolution(dist, V);
}

// comparing hospital on basis of distance

bool comp(pair<int, hospital> a, pair<int, hospital> b)
{
  return a.first < b.first;
}

// comparing hospital on basis of rating

bool comp1(pair<int, hospital> a, pair<int, hospital> b)
{
  return a.second.rating > b.second.rating;
}

// assigning city as per user input

void set_city(vector<city> c, string city)
{

  for (int i = 0; i < 15; i++)
  {
    if (city == c[i].city_name)
    {
      s_c = c[i].city_no;
    }
  }
  cout << endl;
}

// assigning speciality required as per user input

void set_speciality(vector<speciality> s, string disease)
{

  for (int i = 0; i < 3; i++)
  {
    if (disease == s[i].s_name)
    {
      s_s = s[i].s_no;
    }
  }
  cout << s_s;
}

// assining speciality to different hospitals by grapgh coloring

void hos_speciality(vector<hospital> &h, int color[])
{
  int i = 0, x = 0;
  while (i < 15)
  {
    if (color[i] != 0)
    {
      h[x].speciality = color[i];
      x++;
    }
    i++;
  }
}

// using 0/1 knapsack for heathcheckups

int knapsack(int n, int w, vector<health_checkups> hc, vector<vector<int>> &dp)
{
  if (w <= 0)
  {
    return 0;
  }
  if (n <= 0)
  {
    return 0;
  }

  if (dp[n][w] != -1)
  {
    return dp[n][w];
  }
  if (hc[n - 1].price > w)
  {
    dp[n][w] = knapsack(n - 1, w, hc, dp);
  }
  else
  {
    dp[n][w] = max(knapsack(n - 1, w, hc, dp), knapsack(n - 1, w - hc[n - 1].price, hc, dp) + hc[n - 1].benefit);
  }
  return dp[n][w];
}

// backtrack the knapsack and finding out the test can be done

void track_items(vector<vector<int>> &dp, int W, int n, vector<health_checkups> hc)
{
  int res = dp[n][W];

  int w = W;
  for (int i = n; i > 0 && res > 0; i--)
  {

    if (res == dp[i - 1][w])
    {
      continue;
    }
    else
    {

      cout << hc[i - 1].name << endl;
      res = res - hc[i - 1].benefit;
      w = w - hc[i - 1].price;
    }
  }
}

// sorting on basis of hospital distance

bool operator==(const city &c1, const city &c2)
{
  return c1.city_no == c2.city_no;
}

void sort_bydist(vector<pair<int, hospital>> dis_rat, vector<city> c)
{

  sort(dis_rat.begin(), dis_rat.end(), comp);
  cout << endl;
  cout << "distance"
       << "\t"
       << "Rating"
       << "\t\t"
       << "City_no" << endl;
  for (int i = 0; i < 10; i++)
  {
    int j;
    for (j = 0; j < c.size(); j++)
    {
      if (dis_rat[i].second.city == c[j].city_no)
      {
        break;
      }
    }
    cout << dis_rat[i].first << "Km"
         << "\t\t" << dis_rat[i].second.rating << "\t\t" << c[j].city_name << endl;
  }
}

// sorting on basis of distance and showing only specific speciality

void sort_bydist_doctor(vector<pair<int, hospital>> dis_rat, int doctor, vector<city> c)
{
  sort(dis_rat.begin(), dis_rat.end(), comp);
  cout << endl;
  cout << "distance"
       << "\t"
       << "Rating"
       << "\t\t"
       << "City Name" << endl;
  for (int i = 0; i < 10; i++)
  {

    if (dis_rat[i].second.speciality == doctor)
    {
      int j;
      for (j = 0; j < c.size(); j++)
      {
        if (dis_rat[i].second.city == c[j].city_no)
        {
          break;
        }
      }
      cout << dis_rat[i].first << "Km"
           << "\t\t" << dis_rat[i].second.rating << "\t\t" << c[j].city_name << endl;
    }
  }
}

void sort_Rating_doctor(vector<pair<int, hospital>> dis_rat, int doctor, vector<city> c)
{
  sort(dis_rat.begin(), dis_rat.end(), comp1);
  cout << endl;
  cout << "distance"
       << "\t"
       << "Rating"
       << "\t\t"
       << "City Name" << endl;
  for (int i = 0; i < 10; i++)
  {
    if (dis_rat[i].second.speciality == doctor)
    {
      int j;
      for (j = 0; j < c.size(); j++)
      {
        if (dis_rat[i].second.city == c[j].city_no)
        {
          break;
        }
      }
      cout << dis_rat[i].first << "Km"
           << "\t\t" << dis_rat[i].second.rating << "\t\t" << c[j].city_name << endl;
    }
  }
}

// taking patient information

void patient_info(vector<patient> &usr_detail, vector<city> c, vector<speciality> s)
{
  // system("PAUSE");
  // system("CLS");
  struct patient p;
  cout << "\t\t\t\t\tEnter Patient Details \n";
  cout << "\n\t\t\t\t\tenter your name"
       << " ";
  cin >> p.name;

  cout << endl;
  cout << "\t\t\t\t\tenter your age"
       << " ";
  cin >> p.age;

  cout << endl;
  cout << "\t\t\t\t\tenter your city"
       << " ";
  cin >> p.city;

  cout << endl;
  // cout << "enter your disease"
  //      << " ";
  // cin >> p.speciality;
  usr_detail.push_back(p);
  cout << endl;

  set_city(c, p.city);
  ofstream fout("patient.txt", ios::app);
  fout << p.name << endl
       << p.city << endl
       << p.age << endl;
  fout.close();
}

void helt_check(vector<vector<int>> dp, vector<health_checkups> hc, int n)
{
  cout << "Total body check-up = " << knapsack(6, n, hc, dp) << "%" << endl;
  track_items(dp, n, 6, hc);
}

void more_details(vector<pair<int, hospital>> dis_rat, vector<vector<int>> dp, vector<health_checkups> hc, vector<city> c)
{
choice:
  int y;
  int n;
  cout << "\n\n\n\n1. Emergency" << endl;
  cout << "2. for consulting a doctor " << endl;
  cout << "3. Health Check up" << endl;
  cout << "4. Exit" << endl;
  cout << "Enter your prefrence ";
  cin >> n;
  ofstream fout("patient.txt", ios::app);
  switch (n)
  {
  case 1:
    sort_bydist(dis_rat, c);
    break;

  case 2:
    int x;
    cout << "press 1 to consult a cardiologist" << endl;
    cout << "press 2 to consult a gynecologist" << endl;
    cout << "press 3 to consult a neurologist" << endl;
    cin >> x;
    switch (x)
    {
    case 1:
      fout << "cardiologist\n";
      fout.close();
      cout << "press 1 to sort by distance" << endl;
      cout << "press 2 to sort by rating" << endl;
      cin >> y;
      if (y == 1)
      {
        sort_bydist_doctor(dis_rat, 1, c);
      }
      else if (y == 2)
      {
        sort_Rating_doctor(dis_rat, 1, c);
      }
      break;

    case 2:
      fout << "gynecologist\n";
      cout << "press 1 to sort by distance" << endl;
      cout << "press 2 to sort by rating" << endl;
      cin >> y;
      if (y == 1)
      {
        sort_bydist_doctor(dis_rat, 2, c);
      }
      else if (y == 2)
      {
        sort_Rating_doctor(dis_rat, 2, c);
      }
      break;

    case 3:
      fout << "neurologist\n";

      cout << "press 1 to sort by distance" << endl;
      cout << "press 2 to sort by rating" << endl;
      cin >> y;
      if (y == 1)
      {
        sort_bydist_doctor(dis_rat, 3, c);
      }
      else if (y == 2)
      {
        sort_Rating_doctor(dis_rat, 3, c);
      }
      break;

    default:
      break;
    }
    break;
  case 3:
    int n;
    cout << "enter your budget ";
    cin >> n;
    helt_check(dp, hc, n);
    break;
  case 4:
    system("cls");
    exit(1);
  default:
    break;
  }
  goto choice;
}

int main()
{

  vector<patient> usr_detail;
  intro();

  vector<speciality> sp(3);
  sp[0].s_name = "cardiologist";
  sp[0].s_no = 1;

  sp[1].s_name = "gynecologist";
  sp[1].s_no = 2;

  sp[2].s_name = "neurologist";
  sp[2].s_no = 3;

  vector<city> c(15);
  c[0].city_name = "meerut";
  c[0].city_no = 0;
  c[0].hospital = true;

  c[1].city_name = "ghaziabad";
  c[1].city_no = 1;
  c[1].hospital = false;

  c[2].city_name = "noida";
  c[2].city_no = 2;
  c[2].hospital = true;

  c[3].city_name = "delhi";
  c[3].city_no = 3;
  c[3].hospital = true;

  c[4].city_name = "gurugram";
  c[4].city_no = 4;
  c[4].hospital = false;

  c[5].city_name = "faridabad";
  c[5].city_no = 5;
  c[5].hospital = true;

  c[6].city_name = "lucknow";
  c[6].city_no = 6;
  c[6].hospital = false;

  c[7].city_name = "shimla";
  c[7].city_no = 7;
  c[7].hospital = true;

  c[8].city_name = "bangalore";
  c[8].city_no = 8;
  c[8].hospital = true;

  c[9].city_name = "hyderabad";
  c[9].city_no = 9;
  c[9].hospital = true;

  c[10].city_name = "surat";
  c[10].city_no = 10;
  c[10].hospital = false;

  c[11].city_name = "mumbai";
  c[11].city_no = 11;
  c[11].hospital = true;

  c[12].city_name = "pune";
  c[12].city_no = 12;
  c[12].hospital = false;

  c[13].city_name = "chennai";
  c[13].city_no = 13;
  c[13].hospital = true;

  c[14].city_name = "jaipur";
  c[14].city_no = 14;
  c[14].hospital = true;

  vector<hospital> h(10);
  h[0].city = 0;
  h[0].name = "";
  h[0].rating = 8.2;
  h[0].reg_no = 6969;

  h[1].city = 2;
  h[1].name = "";
  h[1].rating = 8.8;
  h[1].reg_no = 0;

  h[2].city = 3;
  h[2].name = "";
  h[2].rating = 7.9;
  h[2].reg_no = 7425;

  h[3].city = 5;
  h[3].name = "";
  h[3].rating = 5.3;
  h[3].reg_no = 7443;

  h[4].city = 7;
  h[4].name = "";
  h[4].rating = 7.6;
  h[4].reg_no = 0;

  h[5].city = 8;
  h[5].name = "";
  h[5].rating = 9.3;
  h[5].reg_no = 3258;

  h[6].city = 9;
  h[6].name = "";
  h[6].rating = 7.9;
  h[6].reg_no = 0;

  h[7].city = 11;
  h[7].name = "";
  h[7].rating = 9.6;
  h[7].reg_no = 3569;

  h[8].city = 13;
  h[8].name = "";
  h[8].rating = 5.1;
  h[8].reg_no = 3514;

  h[9].city = 14;
  h[9].name = "";
  h[9].rating = 8.0;
  h[9].reg_no = 7823;

  vector<vector<int>> hos_graph{
      {0, 3, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {3, 0, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {5, 7, 0, 5, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {2, 6, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 9, 0, 0, 10, 0, 7, 13, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 10, 0, 11, 4, 0, 2, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 11, 0, 12, 0, 8, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 7, 4, 12, 0, 3, 12, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 13, 0, 0, 3, 0, 11, 6, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 2, 8, 12, 11, 0, 5, 0, 0, 6, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 6, 5, 0, 11, 9, 8, 0},
      {0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 11, 0, 4, 0, 0},
      {0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 9, 4, 0, 7, 5},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 0, 7, 0, 9},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 9, 0},
  };

  vector<health_checkups> hc(6);
  hc[0].name = "CT-Scan";
  hc[0].price = 3000;
  hc[0].benefit = 13;

  hc[1].name = "MRI";
  hc[1].price = 6000;
  hc[1].benefit = 15;

  hc[2].name = "ECG";
  hc[2].price = 300;
  hc[2].benefit = 9;

  hc[3].name = "blood test";
  hc[3].price = 700;
  hc[3].benefit = 8;

  hc[4].name = "urine-test";
  hc[4].price = 400;
  hc[4].benefit = 5;

  hc[5].name = "Spirometry"; // lungs
  hc[5].price = 2500;
  hc[5].benefit = 11;

  int colour[15];

  for (int i = 0; i < 15; i++)
  {
    colour[i] = 0;
  }

  if (colouring(hos_graph, 15, 0, colour, 10, c))
  {
    for (int i = 0; i < 15; i++)
    {
      h[i].speciality = colour[i];
    }
  }

  hos_speciality(h, colour);

  // for(int i=0;i<10;i++)
  // {
  //     cout<<h[i].speciality<<endl;
  // }

  vector<pair<int, hospital>> dis_rat(10);

  patient_info(usr_detail, c, sp);

  int dis[15];

  dijkstra(hos_graph, 0, 15, dis);

  int i = 0, x = 0;
  while (i < 15)
  {
    if (c[i].hospital != false)
    {
      dis_rat[x] = {dis[i], h[x]};
      x++;
    }
    i++;
  }

  vector<vector<int>> dp(5001, vector<int>(5001, -1));
  more_details(dis_rat, dp, hc, c);
  return 0;
}