### Вывод чисел в диапазоне от -55.0 до 99.9 с шагом 0.1 и в диапазоне от 100 до 125 с шагом 1 для индикатора символа "минус" и 3-х семисегментных индикаторов

<table>
  <tr>
    <th>S</th>
    <th>I0</th>
    <th>I1</th>
    <th>I2</th>
    <th>Диапазон</th>
    <th>S</th>
    <th>I0</th>
    <th>I1</th>
    <th>I2</th>
  </tr>
  <tr>
    <td align="center">-</td>
    <td align="center">5</td>
    <td align="center">5.</td>
    <td align="center">0</td>
    <td align="center" rowspan="3">(-inf; -10]</td>
    <td align="center" rowspan="3">s</td>
    <td align="center" rowspan="3">d1</td>
    <td align="center" rowspan="3">d0.</td>
    <td align="center" rowspan="3">f0</td>
  </tr>
  <tr>
    <td align="center" colspan="4">...</td>
  </tr>
  <tr>
    <td align="center">-</td>
    <td align="center">1</td>
    <td align="center">0.</td>
    <td align="center">0</td>
  </tr>
  <tr>
    <td align="center"></td>
    <td align="center">-</td>
    <td align="center">9.</td>
    <td align="center">9</td>
    <td align="center" rowspan="3">(-10; 0)</td>
    <td align="center" rowspan="3"></td>
    <td align="center" rowspan="3">s</td>
    <td align="center" rowspan="3">d0.</td>
    <td align="center" rowspan="3">f0</td>
  </tr>
  <tr>
    <td align="center" colspan="4">...</td>
  </tr>
  <tr>
    <td align="center"></td>
    <td align="center">-</td>
    <td align="center">0.</td>
    <td align="center">1</td>
  </tr>
  <tr>
    <td align="center"></td>
    <td align="center"></td>
    <td align="center">0.</td>
    <td align="center">0</td>
    <td align="center" rowspan="3">[0; 10)</td>
    <td align="center" rowspan="3"></td>
    <td align="center" rowspan="3">s</td>
    <td align="center" rowspan="3">d0.</td>
    <td align="center" rowspan="3">f0</td>
  </tr>
  <tr>
    <td align="center" colspan="4">...</td>
  </tr>
  <tr>
    <td align="center"></td>
    <td align="center"></td>
    <td align="center">9.</td>
    <td align="center">9</td>
  </tr>
  <tr>
    <td align="center"></td>
    <td align="center">1</td>
    <td align="center">0.</td>
    <td align="center">0</td>
    <td align="center" rowspan="3">[10; 100)</td>
    <td align="center" rowspan="3">s</td>
    <td align="center" rowspan="3">d1</td>
    <td align="center" rowspan="3">d0.</td>
    <td align="center" rowspan="3">f0</td>
  </tr>
  <tr>
    <td align="center" colspan="4">...</td>
  </tr>
  <tr>
    <td align="center"></td>
    <td align="center">9</td>
    <td align="center">9.</td>
    <td align="center">9</td>
  </tr>
  <tr>
    <td align="center"></td>
    <td align="center">1</td>
    <td align="center">0</td>
    <td align="center">0</td>
    <td align="center" rowspan="3">[100; +inf)</td>
    <td align="center" rowspan="3">s</td>
    <td align="center" rowspan="3">d2</td>
    <td align="center" rowspan="3">d1</td>
    <td align="center" rowspan="3">d0</td>
  </tr>
  <tr>
    <td align="center" colspan="4">...</td>
  </tr>
  <tr>
    <td align="center"></td>
    <td align="center">1</td>
    <td align="center">2</td>
    <td align="center">5</td>
  </tr>
</table>

#### Обозначения

**S** - индикатор символа "минус" (может быть включен или выключен)

**I0, I1, I2** - индикаторы (слева направо)

**d2** - разряд сотен

**d1** - разряд десятков

**d0** - разряд единиц

**d0.** - разряд единиц с точкой

**s** - символ "минус", если число отрицательное; пустой символ, если число положительное или ноль
