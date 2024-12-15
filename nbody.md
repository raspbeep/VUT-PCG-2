# PCG projekt 2
- autor: xkrato61

## Měření výkonu (čas / 100 kroků simulace)

### Průběžné
|   N   | CPU [s]  | Step 0 [s] | Step 1 [s] |
|:-----:|----------|------------|------------|
|  4096 | 0.492139 |  0.081679  |  0.067626  |
|  8192 | 1.471328 |  0.158931  |  0.134522  |
| 12288 | 2.478942 |  0.235794  |  0.200762  |
| 16384 | 3.386801 |  0.333549  |  0.274931  |
| 20480 | 5.059240 |  0.417726  |  0.344629  |
| 24576 | 7.112179 |  0.499557  |  0.413462  |
| 28672 | 9.892856 |  0.599185  |  0.481295  |
| 32768 | 12.59829 |  0.688993  |  0.548345  |
| 36864 | 15.54297 |  0.774345  |  0.615358  |
| 40960 | 19.36099 |  0.860062  |  0.682265  |
| 45056 | 23.48723 |  1.310660  |  0.760266  |
| 49152 | 27.69359 |  1.431970  |  0.829823  |
| 53248 | 32.63063 |  1.552383  |  0.899366  |
| 57344 | 37.43660 |  1.968181  |  0.968129  |
| 61440 | 42.85863 |  2.112641  |  1.038618  |
| 65536 | 49.46104 |  2.252345  |  1.107857  |
| 69632 | 55.14939 |  2.725818  |  1.182968  |
| 73728 | 62.04446 |  2.924096  |  1.289774  |
| 77824 | 69.26138 |  3.088462  |  1.361360  |
| 81920 | 76.60071 |  3.249822  |  1.433266  |

### Závěrečné
|    N   |  CPU [s] | GPU [s]  | Zrychlení | Propustnost [GiB/s] | Výkon [GFLOPS] |
|:------:|:--------:|:--------:|:---------:|:-------------------:|:--------------:|
|   1024 |   1.0928 | 0.032983 |  33.1322  |     0.166143        |        98      |
|   2048 |   0.5958 | 0.049000 |  12.1592  |     0.145605        |       195      |
|   4096 |   0.6652 | 0.081636 |  8.1484   |     0.144766        |       389      |
|   8192 |   1.6599 | 0.147070 |  11.2865  |     0.144375        |       776      |
|  16384 |   3.3655 | 0.286343 |  11.7534  |     0.140381        |      1512      |
|  32768 |  12.7233 | 0.555099 |  22.9208  |     0.140459        |      3028      |
|  65536 |  48.9732 | 1.107961 |  44.2012  |     0.138535        |      5975      |
| 131072 | 195.9965 | 4.442266 |  44.1208  |     0.068037        |      5867      |

## Otázky

### Krok 0: Základní implementace
**Vyskytla se nějaká anomále v naměřených časech? Pokud ano, vysvětlete:**
Pre step0 som pozoroval 3 vyrazne skoky (figure.png) v casoch. Podla zisteni z nastroja 
Nvdia Nsight Compute, skoky nastavaju kvoli cakaniu na pamatove operacie (warp stall).
Najvacsie cakanie nastavalo pri nahravani dat druhej particle
`const float4 otherParticle = p.positions_weights[j];` a pri matematicky najnarocnejsej
casti vypoctu `const float f = G * otherParticle.w / (r3 + FLT_MIN);`.

Pozorovane narasty v casoch vykonavania by sa dali vysvetlit:
1. vycerpanim poctov registrov/zdielanej pamate na SM
2. prekrocenie L2 cache kapacity alebo cache bandwidth saturacii

### Krok 1: Sloučení kernelů
**Došlo ke zrychlení?**
Doslo k vyraznemu zrychleniu, obzvlast pre vacsie pocty castic. Ako vidno v prilozenom grafe
(figure.png), do velkosti 40960 castic su rozdiely zanedbatelne, no no pri velkosti
45056 castic je cas Step0 takmer dvojnasobny oproti step1. 

**Popište hlavní důvody:**
Dovody zrychlenia po zluceni kernelov su: nizsia rezia pri spusteni jedneho kernelu namiesto troch a lepsie
znovupouzitie pamate (kedze v algoritme je to "najdrahsia" operacia).

### Krok 2: Výpočet těžiště
**Kolik kernelů je nutné použít k výpočtu?**
Stacil jeden.

**Kolik další paměti jste museli naalokovat?**
4 float -> 16B

**Jaké je zrychelní vůči sekveční verzi? Zdůvodněte.** *(Provedu to smyčkou #pragma acc parallel loop seq)*
Zvolil som odlisny pristup vypoctu oproti referencej CPU verzii. Kym CPU implementacia pouziva
inkrementalnu metodu, ja pocitam COM ako priamy vazeny sucet pozicii. Tento pristup
som zvolil kvoli mensej nachylnosti na akumulovane numericke chyby za cenu niektorych narocnejsich operacii
(3 delenia pri kazdom vypocte). Z tohto dovodu sa moje vysledky taziska lisia od referencnej (N=4096, steps=100),
no rozdiely su stale zanedbatelne.
Namiesto dovetku seq vyuzivam reduction pre jednotlive hodnoty taziska (jeho poloha a celkova hmotnost systemu).

### Krok 4: Měření výkonu
**Jakých jste dosáhli výsledků?**
So zvysujucim sa poctom castic vyrazne narasta znovupouzite dat pri vypocte. To znamena ze pri
vacsich systemoch nie je vypocet brzdeny priepustnostou pamate ale iba samotnym vykonom akceleratora.
Pri velkosti N=65536 a N=131072 som narazil na limit vypoctovy limit ~6TF co je vsak stale hlboko
pod teoretickym vykonom karty (19.5TF).

**Lze v datech pozorovat nějaké anomálie?**
Vo vysledkoch mozno vidiet prudky pokles priepustnosti pamati medzi poctom castic N=65536
(0.138GiB/s) a N=131072 (0.068037GiB/s).
