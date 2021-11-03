## Qt/SQLite

```
Query: "SELECT Card.ID, Card.Qt, Nom.Nm FROM Card INNER JOIN Nom on Nom.ID = Card.Nom_ID ;"
Result1: 
1|10|Стол
2|20|Стул
3|25|Шкаф
4|45|Кресло
5|7|Стул
6|17|Стол
7|45|Ваза
8|34|Шкаф
9|6|Стул 

Query: "SELECT Card.ID, Card.Qt, Party.Nm FROM Card INNER JOIN Party ON Party.ID = Card.Party_ID ;"
Result2: 
2|20|Первая
4|45|Вторая
6|17|Третья
7|45|Третья
8|34|Третья
9|6|Первая 

Query: "SELECT ca.ID, cr1.Nm, cr2.Nm FROM Card ca INNER JOIN Contractor cr1 ON cr1.ID = ca.Owner_ID INNER JOIN Contractor cr2 ON cr2.ID = ca.Customer_ID ;"
Result3: 
5|ООО "Веллатрест"|ООО "ПРОГРЕСС"
8|ООО "ПРОГРЕСС"|"УКРСПЕЦЭКСПОРТ" 

Query: "SELECT Contractor.Nm FROM Contractor UNION ALL SELECT Store.Nm FROM Store ;"
Result4: 
ООО "Веллатрест"
ООО "Оникс"
ООО "ПРОГРЕСС"
ООО "Интеллект Сервис"
"УКРСПЕЦЭКСПОРТ"
Готовая продукция
Товары на складе
Сырье и материалы 

Query: "SELECT Card.Store_ID, SUM(Qt) FROM Card GROUP BY Card.Store_ID ;"
Result5: 
1|55
2|114
3|40 

Query: "SELECT Nom.Nm FROM Nom WHERE Nom.ID NOT IN (SELECT Card.Nom_ID FROM Card) ;"
Result6: 

Тумбочка
Люстра 
```

