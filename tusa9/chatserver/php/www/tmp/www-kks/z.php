<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
 <head>
   <meta http-equiv="Content-Type" content="text/html; charset=windows-1251">
     <title>hover</title>
       <style type="text/css">
          UL {
	      width: 180px; /* Ширина меню */
	          list-style: none; /* Для списка убираем маркеры */
		      margin: 0; /* Нет отступов вокруг */
		          padding: 0; /* Убираем поля вокруг текста */
			      font-family: Arial, sans-serif; /* Рубленый шрифт для текста меню */
			          font-size: 10pt; /* Размер названий в пункте меню */
				     }
				        UL LI  {
					    position: relative; /* Подпункты позиционируются относительно */
					       }
					          LI UL {
						      position: absolute; /* Подменю позиционируются абсолютно */
						          display: none; /* Скрываем подменю */
							      top: 0; /* По высоте положение подменю исходное */
							          left: 179px; /* Сдвигаем подменю вправо */
								      z-index: 1; /* Основное меню находится ниже подменю */
								         }
									    LI A {
									        display: block; /* Ссылка как блочный элемент */
										    width: 100%; /* Ссылка на всю ширину пункта */
										        padding: 5px; /* Поля вокруг надписи */
											    text-decoration: none; /* Подчеркивание у ссылок убираем */
											        color: #666; /* Цвет текста */
												    border: 1px solid #ccc;	/* Рамка вокруг пунктов меню */
												        background-color: #f0f0f0; /* Цвет фона */
													    border-bottom: none; /* Границу снизу не проводим */
													       }
													          LI A:hover {
														      color: #ffe; /* Цвет текста активного пункта */
														          background-color: #5488af; /* Цвет фона активного пункта */
															     }
															        LI:hover UL, LI.over UL { 
																    display: block; /* При выделении пункта курсором мыши отображается подменю */
																       }
																          .brd {
																	      border-bottom: 1px solid #ccc; /* Линия снизу */
																	         }
																		   </style>
																		    </head>
																		     <body>
																		     
																		       <ul id="menu">
																		          <li><a href="russian.html">Русская кухня</a>
																			      <ul> 
																			           <li><a href="linkr1.html">Бефстроганов</a></li> 
																				        <li><a href="linkr2.html">Гусь с яблоками</a></li> 
																					     <li><a href="linkr3.html">Крупеник новгородский</a></li> 
																					          <li><a href="linkr4.html" class="brd">Раки по-русски</a></li> 
																						      </ul> 
																						         </li> 
																							    <li><a href="ukrainian.html">Украинская кухня</a> 
																							        <ul> 
																								     <li><a href="linku1.html">Вареники</a></li> 
																								          <li><a href="linku2.html">Жаркое по-харьковски</a></li> 
																									       <li><a href="linku3.html">Капустняк черниговский</a></li> 
																									            <li><a href="linku4.html" class="brd">Потапцы с помидорами</a></li> 
																										        </ul> 
																											   </li>
																											      <li><a href="caucasus.html">Кавказская кухня</a> 
																											          <ul> 
																												       <li><a href="linkc1.html">Суп-харчо</a></li> 
																												            <li><a href="linkc2.html">Лилибдж</a></li> 
																													         <li><a href="linkc3.html">Чихиртма</a></li> 
																														      <li><a href="linkc4.html" class="brd">Шашлык</a></li> 
																														          </ul> 
																															     </li> 
																															        <li><a href="asia.html" class="brd">Кухня Средней Азии</a></li> 
																																  </ul>
																																  
																																   </body>
																																   </html>