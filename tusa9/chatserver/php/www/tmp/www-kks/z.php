<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">
<html>
 <head>
   <meta http-equiv="Content-Type" content="text/html; charset=windows-1251">
     <title>hover</title>
       <style type="text/css">
          UL {
	      width: 180px; /* ������ ���� */
	          list-style: none; /* ��� ������ ������� ������� */
		      margin: 0; /* ��� �������� ������ */
		          padding: 0; /* ������� ���� ������ ������ */
			      font-family: Arial, sans-serif; /* �������� ����� ��� ������ ���� */
			          font-size: 10pt; /* ������ �������� � ������ ���� */
				     }
				        UL LI  {
					    position: relative; /* ��������� ��������������� ������������ */
					       }
					          LI UL {
						      position: absolute; /* ������� ��������������� ��������� */
						          display: none; /* �������� ������� */
							      top: 0; /* �� ������ ��������� ������� �������� */
							          left: 179px; /* �������� ������� ������ */
								      z-index: 1; /* �������� ���� ��������� ���� ������� */
								         }
									    LI A {
									        display: block; /* ������ ��� ������� ������� */
										    width: 100%; /* ������ �� ��� ������ ������ */
										        padding: 5px; /* ���� ������ ������� */
											    text-decoration: none; /* ������������� � ������ ������� */
											        color: #666; /* ���� ������ */
												    border: 1px solid #ccc;	/* ����� ������ ������� ���� */
												        background-color: #f0f0f0; /* ���� ���� */
													    border-bottom: none; /* ������� ����� �� �������� */
													       }
													          LI A:hover {
														      color: #ffe; /* ���� ������ ��������� ������ */
														          background-color: #5488af; /* ���� ���� ��������� ������ */
															     }
															        LI:hover UL, LI.over UL { 
																    display: block; /* ��� ��������� ������ �������� ���� ������������ ������� */
																       }
																          .brd {
																	      border-bottom: 1px solid #ccc; /* ����� ����� */
																	         }
																		   </style>
																		    </head>
																		     <body>
																		     
																		       <ul id="menu">
																		          <li><a href="russian.html">������� �����</a>
																			      <ul> 
																			           <li><a href="linkr1.html">������������</a></li> 
																				        <li><a href="linkr2.html">���� � ��������</a></li> 
																					     <li><a href="linkr3.html">�������� ������������</a></li> 
																					          <li><a href="linkr4.html" class="brd">���� ��-������</a></li> 
																						      </ul> 
																						         </li> 
																							    <li><a href="ukrainian.html">���������� �����</a> 
																							        <ul> 
																								     <li><a href="linku1.html">��������</a></li> 
																								          <li><a href="linku2.html">������ ��-����������</a></li> 
																									       <li><a href="linku3.html">��������� ������������</a></li> 
																									            <li><a href="linku4.html" class="brd">������� � ����������</a></li> 
																										        </ul> 
																											   </li>
																											      <li><a href="caucasus.html">���������� �����</a> 
																											          <ul> 
																												       <li><a href="linkc1.html">���-�����</a></li> 
																												            <li><a href="linkc2.html">�������</a></li> 
																													         <li><a href="linkc3.html">��������</a></li> 
																														      <li><a href="linkc4.html" class="brd">������</a></li> 
																														          </ul> 
																															     </li> 
																															        <li><a href="asia.html" class="brd">����� ������� ����</a></li> 
																																  </ul>
																																  
																																   </body>
																																   </html>