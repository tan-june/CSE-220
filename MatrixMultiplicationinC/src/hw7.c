#include "hw7.h"
#include <stdbool.h>

matrix_sf *add_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2)
{

  if ((mat1->num_rows != mat2->num_rows) || (mat1->num_cols != mat2->num_cols))
  {
    return NULL;
  }

  matrix_sf *result = malloc(sizeof(matrix_sf) + (mat1->num_rows * (mat2->num_cols) * sizeof(int)));
  result->name = 'C';
  result->num_rows = mat1->num_rows;
  result->num_cols = mat1->num_cols;
  int arraylencalc = mat1->num_rows * mat1->num_cols;

  // Add Mat1 and Mat 2 into result array
  for (int i = 0; i < arraylencalc; i++)
  {
    // int value = (mat1->values[i] + mat2->values[i]);
    // printf("Mat 1 Value:          %d\n", mat1->values[i]);
    // printf("Mat 2 Value:          %d\n", mat2->values[i]);
    // printf("Value Added Together: %d\n",value);
    result->values[i] = ((mat1->values[i]) + (mat2->values[i]));
  }

  // printf("Matrix Name: %c\n", mat1->name);
  // printf("Matrix Values:\n");
  // for(int i = 0; i<arraylencalc; i++){
  //   printf("%d ", mat1-> values[i]);
  // }
  // printf("\n\n");
  // print_matrix_sf(mat1);
  // print_matrix_sf(mat2);
  // print_matrix_sf(result);

  return result;
}

matrix_sf *mult_mats_sf(const matrix_sf *mat1, const matrix_sf *mat2)
{

  if (mat1->num_cols != mat2->num_rows)
  {
    return NULL;
  }

  matrix_sf *result = malloc(sizeof(matrix_sf) + (mat1->num_rows * (mat2->num_cols) * sizeof(int)));
  result->name = 'C';
  result->num_rows = mat1->num_rows;
  result->num_cols = mat2->num_cols;

  for (unsigned int i = 0; i < mat1->num_rows; i++)
  {
    for (unsigned int j = 0; j < mat2->num_cols; j++)
    {
      int sum = 0;
      for (unsigned int k = 0; k < mat1->num_cols; k++)
      {
        int val1Index = i * mat1->num_cols + k;
        int val2Index = k * mat2->num_cols + j;
        // printf("Value 1 Index: %d", val1Index);
        // printf("Value 2 Index: %d", val2Index);

        int value1 = mat1->values[val1Index];
        int value2 = mat2->values[val2Index];
        // printf("Value 1: %d", value1);
        // printf("Value 2: %d", value2);

        sum += value1 * value2;      
        // printf("Sum of Row*Col: %d", sum); 
               
      }

      int indexcalc = i * result->num_cols + j;
      result->values[indexcalc] = sum;
      // printf("Multiplied Value: %d\n",result->values[indexcalc]);
    }
  }
  return result;
}

matrix_sf *transpose_mat_sf(const matrix_sf *mat)
{

  matrix_sf *result = malloc(sizeof(matrix_sf) + (mat->num_rows * (mat->num_cols) * sizeof(int)));
  result->name = mat->name;
  result->num_rows = mat->num_cols;
  result->num_cols = mat->num_rows;

  for (unsigned int i = 0; i < mat->num_rows; i++)
  {
    for (unsigned int j = 0; j < mat->num_cols; j++)
    {
      // printf("(%d,%d)", i,j);

      // basis of transpose
      // place (i,j) in (j,i)
      result->values[j * mat->num_rows + i] = mat->values[i * mat->num_cols + j];
    }
  }
  // print_matrix_sf(mat);
  // print_matrix_sf(result);
  return result;
}

bst_sf *insert_bst_sf(matrix_sf *mat, bst_sf *root)
{

  if (root == NULL)
  {
    root = malloc(sizeof(bst_sf));
    root->right_child = NULL;
    root->left_child = NULL;
    root->mat = mat;
    return root;
  }

  if (mat->name < root->mat->name)
  {
    // less than go left
    root->left_child = insert_bst_sf(mat, root->left_child);
  }
  else if (mat->name > root->mat->name)
  {
    // greater than go right
    root->right_child = insert_bst_sf(mat, root->right_child);
  }
  else
  {
    return root;
  }

  return root;
}

matrix_sf *find_bst_sf(char name, bst_sf *root)
{
  if (root == NULL)
  {
    return NULL;
  }
  if (name == root->mat->name)
  {
    return root->mat;
  }
  else if (name < root->mat->name)
  {
    return find_bst_sf(name, root->left_child);
  }
  else if (name > root->mat->name)
  {
    return find_bst_sf(name, root->right_child);
  }
  return NULL;
}

void free_bst_sf(bst_sf *root)
{
  if (root == NULL)
  {
    return;
  }
  free_bst_sf(root->left_child);
  free_bst_sf(root->right_child);
  // free(root->mat->values);
  free(root->mat);
  free(root);
}

// Adapted from Source Given by Professor McDonell
int precedence(char operator)
{
  switch (operator)
  {
  case '+':
    return 1;
  case '*':
    return 2;
    // transpose
  case '\'':
    return 3;
  default:
    return -1;
  }
}

int isOperator(char ch)
{
  return (ch == '+' || ch == '\'' || ch == '*');
}

char *infix2postfix_sf(char *infix)
{
  int str_len = strlen(infix);
  char *postfix = (char *)malloc(sizeof(char) * (str_len + 2));
  char stack[100];
  int top = -1;
  int postfix_index = 0;
  for (int i = 0; i < str_len; i++)
  {
    if (infix[i] == ' ')
    {
      continue;
    }
    if (isdigit(infix[i]) || isalpha(infix[i]))
    {
      postfix[postfix_index] = infix[i];
      postfix_index++;
    }
    else if (infix[i] == '(')
    {
      stack[++top] = infix[i];
    }
    else if (infix[i] == ')')
    {
      while (top > -1 && stack[top] != '(')
        postfix[postfix_index++] = stack[top--];
      if (top > -1 && stack[top] != '(')
        return NULL;
      else
        top--;
    }
    else if (isOperator(infix[i]))
    {
      while (top > -1 && precedence(stack[top]) >= precedence(infix[i]))
      {
        postfix[postfix_index++] = stack[top];
        top--;
      }
      stack[++top] = infix[i];
    }
  }
  while (top > -1)
  {
    if (stack[top] == '(')
    {
      return NULL;
    }
    postfix[postfix_index++] = stack[top--];
  }
  postfix[postfix_index] = '\0';
  return postfix;
}

matrix_sf *create_matrix_sf(char name, const char *expr)
{

  int num_rows = 0;
  int num_cols = 0;

  // char expr_copy1[strlen(expr) + 1];
  // strcpy(expr_copy1, expr);
  // char* p = strtok(expr_copy1, " ");
  // num_rows = strtol(p);
  // p = strtok(NULL, " ");
  // num_cols = atoi(p);

  char expr_copy1[strlen(expr) + 1];
  strcpy(expr_copy1, expr);

  char *p = strtok(expr_copy1, " ");
  num_rows = strtol(p, NULL, 10);

  p = strtok(NULL, " ");
  num_cols = strtol(p, NULL, 10);

  char *expr_copy = expr;
  while (*expr_copy != '[')
  {
    expr_copy++;
  }
  expr_copy++;

  if(num_rows == 0 || num_rows == NULL || num_cols == 0 || num_cols == NULL){
    return NULL;
  }

  matrix_sf *result = NULL;
  result = malloc((sizeof(matrix_sf) + ((num_cols * num_rows) * sizeof(int))));
  result->name = name;
  result->num_rows = num_rows;
  result->num_cols = num_cols;

  int memIndex = 0;
  for (int i = 0; i < (num_cols * num_rows); i++)
  {

    // skip all white space, ; and ,
    while (*expr_copy == ' ' || *expr_copy == ',' || *expr_copy == ';')
    {
      expr_copy++;
    }

    int val = atoi(expr_copy);
    result->values[memIndex] = val;
    memIndex++;

    //move to next value
    while (*expr_copy != ' ' && *expr_copy != ';' && *expr_copy != ']')
    {
      expr_copy++;
    }
  }
  return result;
}

matrix_sf *evaluate_expr_sf(char name, char *expr, bst_sf *root)
{

  char *postfix_exp = infix2postfix_sf(expr);
  // printf("Postfix Expression: %s\n", postfix_exp);
  // fflush(stdout);
  matrix_sf *stack[MAX_LINE_LEN];
  int top = -1;

  for (int i = 0; postfix_exp[i] != '\0'; i++)
  {

    if (isalpha(postfix_exp[i]))
    {
      matrix_sf *matrix = find_bst_sf(postfix_exp[i], root);
      // print_matrix_sf(matrix);
      top++;
      stack[top] = matrix;
    }

    else if (postfix_exp[i] == '\'')
    {
      matrix_sf *poppedElement = stack[top];
      top--;
      matrix_sf *transposed = transpose_mat_sf(poppedElement);
      // print_matrix_sf(transposed);
      transposed->name = '?';
      if (poppedElement->name == '?')
      {
        free(poppedElement);
      }
      top++;
      stack[top] = transposed;
      //   free(poppedElement);
    }

    else
    {
      matrix_sf *operator2 = stack[top];
      top--;
      matrix_sf *operator1 = stack[top];
      top--;
      matrix_sf *result;

      if (postfix_exp[i] == '*')
      {
        result = mult_mats_sf(operator1, operator2);
        result->name = '?';
        if (operator1->name == '?')
        {
          free(operator1);
        }
        if (operator2->name == '?')
        {
          free(operator2);
        }
      }

      else if (postfix_exp[i] == '+')
      {
        result = add_mats_sf(operator1, operator2);
        result->name = '?';
        if (operator1->name == '?')
        {
          free(operator1);
        }
        if (operator2->name == '?')
        {
          free(operator2);
        }
      }

      stack[++top] = result;
      //   free(operator1);
      //   free(operator2);
    }
  }

  // print_matrix_sf(stack[top]);
  //   matrix_sf * end_result = malloc(sizeof(matrix_sf) + (cols * rows * sizeof(int)));
  //   end_result->name = name;
  //   end_result -> num_cols = cols;
  //   end_result -> num_rows = rows;
  //   memcpy(end_result -> values, stack[top] -> values, cols*rows*sizeof(int));
  //   top--;

  //   root = insert_bst_sf(end_result, root);

  matrix_sf *end_result = stack[top];
  end_result->name = name;
  top--;

  free(postfix_exp);

  return end_result;
}

matrix_sf *execute_script_sf(char *filename)
{
  FILE *file = fopen(filename, "r");
  
  if(file == NULL){
    return NULL;
  }

  char *line = NULL; //have to free
  size_t max_line_size = MAX_LINE_LEN;
  bst_sf *root = NULL;
  matrix_sf *result = NULL;

  char name;
  while (getline(&line, &max_line_size, file) != -1)
  {
    name = line[0];
    //get to after the = sign
    char *expression = strchr(line, '=');
    expression++;

    if (strchr(expression, '[') != NULL)
    {
      matrix_sf *create = create_matrix_sf(name, expression);
      if (root == NULL)
      {
        root = insert_bst_sf(create, root);
      }
      else
      {
        insert_bst_sf(create, root);
      }
      // print_matrix_sf(create);
    }
    else
    {
      matrix_sf *resulting = evaluate_expr_sf(name, expression, root);
      if (root == NULL)
      {
        root = insert_bst_sf(resulting, root);
      }
      else
      {
        insert_bst_sf(resulting, root);
      }
      // print_matrix_sf(resulting);
    }
  }
  free(line);
  fclose(file);

  result = find_bst_sf(name, root);
  matrix_sf *a = copy_matrix(result->num_rows, result->num_cols, result->values);
  a->name = 'C';
  // print_matrix_sf(a);
  free_bst_sf(root);
  // free(root);
  return a;
}

// This is a utility function used during testing. Feel free to adapt the code to implement some of
// the assignment. Feel equally free to ignore it.
matrix_sf *copy_matrix(unsigned int num_rows, unsigned int num_cols, int values[])
{
  matrix_sf *m = malloc(sizeof(matrix_sf) + num_rows * num_cols * sizeof(int));
  m->name = '?';
  m->num_rows = num_rows;
  m->num_cols = num_cols;
  memcpy(m->values, values, num_rows * num_cols * sizeof(int));
  return m;
}
// Don't touch this function. It's used by the testing framework.
// It's been left here in case it helps you debug and test your code.
void print_matrix_sf(matrix_sf *mat)
{
  assert(mat != NULL);
  assert(mat->num_rows <= 1000);
  assert(mat->num_cols <= 1000);
  printf("%d %d ", mat->num_rows, mat->num_cols);
  for (unsigned int i = 0; i < mat->num_rows * mat->num_cols; i++)
  {
    printf("%d", mat->values[i]);
    if (i < mat->num_rows * mat->num_cols - 1)
      printf(" ");
  }
  printf("\n");
}