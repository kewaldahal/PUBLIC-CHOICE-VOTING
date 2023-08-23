// A SIMPLE PUBLIC CHOICE VOTING PROJECT MADE ON C NOT FOR ME BUT MY FRIEND WHO DON'T KNOW HOW TO CODE 😆
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATES 5
#define MAX_CATEGORIES 4
#define MAX_VOTERS 100
#define VOTE_RECORD_FILE "voted_numbers.txt"

struct Candidate {
  char name[50];
  int votes;
};

struct Category {
  char name[50];
  struct Candidate candidates[MAX_CANDIDATES];
};

struct Voter {
  char mobileNumber[15];
};

struct Voter votedNumbers[MAX_VOTERS];
struct Category categories[MAX_CATEGORIES];

int totalVoters = 0;
int totalVotes = 0;

int hasVoted(char *mobileNumber) {
  for (int i = 0; i < totalVoters; i++) {
    if (strcmp(votedNumbers[i].mobileNumber, mobileNumber) == 0) {
      return 1;
    }
  }
  return 0;
}

void recordVote(int categoryIndex, int candidateIndex, char *mobileNumber) {
  categories[categoryIndex].candidates[candidateIndex].votes++;
  strcpy(votedNumbers[totalVoters].mobileNumber, mobileNumber);
  totalVoters++;
  totalVotes++;

  FILE *file = fopen(VOTE_RECORD_FILE, "a");
  if (file != NULL) {
    fprintf(file, "%s,%s,%s\n", mobileNumber, categories[categoryIndex].name,
            categories[categoryIndex].candidates[candidateIndex].name);
    fclose(file);
  }

  printf("Vote recorded successfully!\n");
}

void displayVotes() {
  printf("Vote count:\n");
  for (int i = 0; i < MAX_CATEGORIES; i++) {
    printf("%s:\n", categories[i].name);
    for (int j = 0; j < MAX_CANDIDATES; j++) {
      printf("%s: %d votes\n", categories[i].candidates[j].name,
             categories[i].candidates[j].votes);
    }
  }
  printf("Total votes: %d\n", totalVotes);
}

void findLeadingCandidate() {
  printf("Leading candidates:\n");
  for (int i = 0; i < MAX_CATEGORIES; i++) {
    int maxVotes = 0;
    int leadingCandidateIndex = -1;
    for (int j = 0; j < MAX_CANDIDATES; j++) {
      if (categories[i].candidates[j].votes > maxVotes) {
        maxVotes = categories[i].candidates[j].votes;
        leadingCandidateIndex = j;
      }
    }

    if (leadingCandidateIndex != -1) {
      printf("%s: %s with %d votes\n", categories[i].name,
             categories[i].candidates[leadingCandidateIndex].name, maxVotes);
    } else {
      printf("%s: No leading candidate yet.\n", categories[i].name);
    }
  }
}

void clearConsole() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void waitForEnter() {
  printf("Press Enter to continue...");
  getchar();
  getchar();
}

int main() {
  strcpy(categories[0].name, "Best Actor");
  strcpy(categories[1].name, "Best Actress");
  strcpy(categories[2].name, "Director");
  strcpy(categories[3].name, "Supporting Actor/Actress");

  strcpy(categories[0].candidates[0].name, "James Bond");
  strcpy(categories[0].candidates[1].name, "Cillian Murphy");
  strcpy(categories[0].candidates[2].name, "Tom Curise");
  strcpy(categories[0].candidates[3].name, "Rajesh Hamal");
  strcpy(categories[0].candidates[4].name, "Anmil KC");

  strcpy(categories[1].candidates[0].name, "Rekha Thapa");
  strcpy(categories[1].candidates[1].name, "Mia Khalifa");
  strcpy(categories[1].candidates[2].name, "Dani Danials");
  strcpy(categories[1].candidates[3].name, "Chindina");
  strcpy(categories[1].candidates[4].name, "Vote gar sex pauxas");

  strcpy(categories[2].candidates[0].name, "Christophar Nolan");
  strcpy(categories[2].candidates[1].name, "James Cameroon");
  strcpy(categories[2].candidates[2].name, "Tatti");
  strcpy(categories[2].candidates[3].name, "Rajkumar Hirani");
  strcpy(categories[2].candidates[4].name, "Kewal Dahal");

  strcpy(categories[3].candidates[0].name, "Actor 1 : Kewal Dahal");
  strcpy(categories[3].candidates[1].name, "Actor 2 : Rajesh Khanna");
  strcpy(categories[3].candidates[2].name, "Actress 1 : Fulmaya Rai");
  strcpy(categories[3].candidates[3].name, "Actress 2 : Vote gar muji");
  strcpy(categories[3].candidates[4].name,
         "Actress 3 : VOTE ME IF YOU WANT SATISFACTION");

  FILE *file = fopen(VOTE_RECORD_FILE, "r");
  if (file != NULL) {
    char mobileNumber[15], categoryName[50], candidateName[50];
    while (fscanf(file, "%[^,],%[^,],%s\n", mobileNumber, categoryName,
                  candidateName) == 3) {
      for (int i = 0; i < MAX_CATEGORIES; i++) {
        if (strcmp(categories[i].name, categoryName) == 0) {
          for (int j = 0; j < MAX_CANDIDATES; j++) {
            if (strcmp(categories[i].candidates[j].name, candidateName) == 0) {
              categories[i].candidates[j].votes++;
              totalVotes++;
              strcpy(votedNumbers[totalVoters].mobileNumber, mobileNumber);
              totalVoters++;
              break;
            }
          }
          break;
        }
      }
    }
    fclose(file);
  }

  int choice;
  char mobileNumber[15];
  int candidateIndex;

  while (1) {
    clearConsole();

    printf("\n--- Public Choice Voting Award ---\n");
    printf("1) Cast your vote\n");
    printf("2) Find votes count\n");
    printf("3) Get leading candidate\n");
    printf("4) Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      printf("Enter your mobile number: ");
      scanf("%s", mobileNumber);

      if (hasVoted(mobileNumber)) {
        printf("You have already voted.\n");
      } else {
        for (int i = 0; i < MAX_CATEGORIES; i++) {
          printf("%d) %s\n", i + 1, categories[i].name);
        }
        printf("Enter the number of the category you want to vote in (0 to "
               "finish): ");
        scanf("%d", &candidateIndex);

        while (candidateIndex >= 1 && candidateIndex <= MAX_CATEGORIES) {
          printf("Candidates for %s:\n", categories[candidateIndex - 1].name);
          for (int i = 0; i < MAX_CANDIDATES; i++) {
            printf("%d) %s\n", i + 1,
                   categories[candidateIndex - 1].candidates[i].name);
          }
          printf("Enter the number of the candidate you want to vote for: ");
          scanf("%d", &choice);

          if (choice >= 1 && choice <= MAX_CANDIDATES) {
            recordVote(candidateIndex - 1, choice - 1, mobileNumber);
          } else {
            printf("Invalid candidate number.\n");
          }

          printf("Enter the number of the category you want to vote in (0 to "
                 "finish): ");
          scanf("%d", &candidateIndex);
        }

        waitForEnter();
      }
      break;
    case 2:
      displayVotes();
      waitForEnter();
      break;
    case 3:
      findLeadingCandidate();
      waitForEnter();
      break;
    case 4:
      file = fopen(VOTE_RECORD_FILE, "w");
      if (file != NULL) {
        for (int i = 0; i < totalVoters; i++) {
          fprintf(file, "%s,%s,%s\n", votedNumbers[i].mobileNumber,
                  "Category Name", "Candidate Name");
        }
        fclose(file);
      } else {
        printf("Error saving voting details.\n");
      }
      exit(0);
    default:
      printf("Invalid choice.\n");
      waitForEnter();
    }
  }

  return 0;
}
