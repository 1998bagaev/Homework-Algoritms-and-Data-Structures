#include <cmath>
#include <fstream>
#include <iostream>


 //Конструктор
 
 list skip_list (list l) 
  {  list lvl = build_lvl(l);                // Здесь происходит построение первого уровня
       while (lvl.size() > 2) 
           lvl = build_lvl (lvl);              // Добавление следующих уровней; последний содержит два элемента
       return t;
  }  
   
  list build_lvl (list lvl)                   // Отсеивание нечётных элементов
   {   list next_lvl; 
       node i = lvl.head();                     // Перебор всех элементов lvl
       while ((i != null) && (i != lvl.tail()))
        {  next_lvl.push_back(node(i.key, i));  // Добавление чётного элемента;
           i = i.next.next;                    // он содержит ключ и ссылку на предыдущий уровень
        }
       return next_lvl; 
   }


//Поиск элемента по ключу:

 T find (list skip_list, K key)
  {   
        
        node res; 
        for (res = skip_list.head; res.ref != null; res = res.ref) 
       {                                     // Cпускаемся на шаг вниз, если можем (п. 3)
           while (res.key <= key)             // Переходим к следующему элементу (п. 2)
               res = res.next(); 
       }
     
     return res.data;
   }
 
//Вставка:
       
  node insert (node i, K key, T data)
   {  
       while (i.key <= key)                  // Ищем подходящее место
           i = i.next(); 
       node tmp = null;                      // Для записи в поле down
       if (i.ref != null)                      // Мы не на нижнем уровне
       {  tmp = insert (i.ref, key);        // Рекурсивный вызов на более низком уровне
           if (tmp == null)                   // Проверка броска монетки
               return null; 
        }
       i.next = new node (i.next, tmp, data, key)  //Непосредственно вставка
        {  if (random(0,1) > 0.5)                 // Бросок монетки
              return i.next;                    // Нужно передать новый элемент для вставки выше
              clock_t end = clock();
              output << (double)(end - start) << std::endl;
         else
              return null;
        }
           
void insert (list skip_list, K key, T data) // Обёрточка
       insert(skip_list.head, key, data)  
   
Удаление:
   
void remove (node i, K key)
       if (i == null)
           return; 
       while (i.key <= key)                   // Ищем элемент
           i = i.next() 
       remove(i.ref, key)                    // Удаляем с нижних уровней
       if i.key == key                      // Если ключ совпадает
           delete(i)                        // удаляем и с этого уровня      
          
void remove (list skip_list, K key) // Обёрточка
       remove(skip_list.head, key) 
