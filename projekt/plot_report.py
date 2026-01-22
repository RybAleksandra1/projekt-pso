import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys

def main():
    if len(sys.argv) < 3:
        print("Użycie: python3 plot_report.py <plik_mapy> <plik_logow>")
        return

    map_file = sys.argv[1]
    log_file = sys.argv[2]

    # --- KONFIGURACJA: TU WPISZ SWOJE ITERACJE ---
    # Możesz zmienić te liczby na dowolne inne, np. [0, 50, 80, 99]
    # Pamiętaj, że w C iteracje zwykle liczymy od 0.
    MOJE_ITERACJE = [0, 5, 10, 25] 
    # ---------------------------------------------

    # 1. WCZYTYWANIE MAPY
    try:
        with open(map_file, 'r') as f:
            header = f.readline().split()
            if not header: raise ValueError("Pusty plik mapy")
            W, H = int(header[0]), int(header[1])
            
            raw_data = f.read().split()
            data = [float(x) for x in raw_data]
            grid = np.array(data).reshape((H, W))
            
            # Znajdź prawdziwy cel
            max_idx = np.argmax(grid)
            peak_y, peak_x = np.unravel_index(max_idx, grid.shape)
            print(f"Mapa: {W}x{H}. Cel: ({peak_x}, {peak_y})")
    except Exception as e:
        print(f"Błąd mapy: {e}")
        return

    # 2. WCZYTYWANIE LOGÓW I WYBÓR ITERACJI
    try:
        df = pd.read_csv(log_file)
        if 'iter' not in df.columns:
            print("Błąd: Brak kolumny 'iter' w CSV.")
            return

        available_iters = df['iter'].unique()
        selected_iters = []

        # Dla każdej liczby, którą chciałaś, sprawdzamy czy istnieje
        for cel in MOJE_ITERACJE:
            if cel in available_iters:
                selected_iters.append(cel)
            else:
                # Jeśli nie ma dokładnie takiej (np. chciałaś 1, a log jest co 10),
                # szukamy najbliższej dostępnej
                closest = min(available_iters, key=lambda x: abs(x - cel))
                print(f"Uwaga: Brak iteracji {cel}, wybrano najbliższą: {closest}")
                if closest not in selected_iters:
                    selected_iters.append(closest)
        
        selected_iters = sorted(selected_iters)

    except Exception as e:
        print(f"Błąd logów: {e}")
        return

    # 3. RYSOWANIE
    fig, axes = plt.subplots(2, 2, figsize=(12, 10))
    axes = axes.flatten()

    for i, it in enumerate(selected_iters):
        # Jeśli użytkownik podał więcej niż 4 iteracje, rysujemy tylko pierwsze 4
        if i >= 4: break 
        
        ax = axes[i]
        
        # Tło
        im = ax.imshow(grid, cmap='terrain', origin='upper', extent=[0, W, H, 0], alpha=0.8)
        
        # Dane
        subset = df[df['iter'] == it]
        
        # Cel (Zielony X)
        ax.scatter(peak_x, peak_y, c='lime', s=150, marker='x', linewidth=3, zorder=10)

        # Drony (Czerwone kropki)
        ax.scatter(subset['x'], subset['y'], c='red', s=20, edgecolors='black', label='Drony')

        # Lider (Gwiazdka)
        if not subset.empty:
            best_idx = subset['val'].idxmax()
            best = subset.loc[best_idx]
            ax.scatter(best['x'], best['y'], c='yellow', s=150, marker='*', edgecolors='black', zorder=9)

        ax.set_title(f"Iteracja: {it}")
        ax.set_xlim(0, W)
        ax.set_ylim(H, 0)

    # Kosmetyka wykresu
    cbar_ax = fig.add_axes([0.92, 0.15, 0.02, 0.7])
    fig.colorbar(im, cax=cbar_ax, label='Wysokość')
    plt.suptitle(f"Ewolucja Roju (Iteracje: {selected_iters})", fontsize=16)
    
    plt.savefig("ewolucja_roju_wybrane.png")
    print("Gotowe! Zapisano: ewolucja_roju_wybrane.png")

if __name__ == "__main__":
    main()