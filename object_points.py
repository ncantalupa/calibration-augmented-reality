import math
import pandas as pd

def generate_points_on_sphere(n, radius=1):
    golden_ratio = (1 + math.sqrt(5)) / 2
    angle_increment = 2 * math.pi * golden_ratio
    points = [(0,0,0)]

    for i in range(n):
        distance = i / n
        inclination = math.acos(1 - 2 * distance)
        azimuth = angle_increment * i
        x = radius * math.sin(inclination) * math.cos(azimuth)
        y = radius * math.sin(inclination) * math.sin(azimuth)
        z = radius * math.cos(inclination)
        points.append((x, y, z))
    return points

points = generate_points_on_sphere(200, 2)
df = pd.DataFrame(points, columns=['x', 'y', 'z'])
df['z'] += 4.0
df['z'] *= -1.0
df['x'] += + 3.0
df['y'] += 4.0
df = df.sort_values(by=['z', 'y', 'x'])
df = df.reset_index(drop=True)
print(df)
df.to_csv('sphere_points.csv', index=True, header=False)