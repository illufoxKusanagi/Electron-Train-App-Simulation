"use client";

import { useState, useEffect } from "react";
import { api } from "@/services/api";
import { SidebarProvider, SidebarTrigger } from "@/components/ui/sidebar";
import { AppSidebar } from "@/components/app-sidebar";
import { ModeToggle } from "@/components/toggle-mode-button";
import { Button } from "@/components/ui/button";
import {
  Card,
  CardContent,
  CardDescription,
  CardHeader,
  CardTitle,
} from "@/components/ui/card";
import { Badge } from "@/components/ui/badge";
import {
  Train,
  MapPin,
  Clock,
  Settings,
  BarChart3,
  Play,
  Zap,
  Users,
  Shield,
  Gauge,
} from "lucide-react";
import Link from "next/link";

export default function Home() {
  const [backendStatus, setBackendStatus] = useState<string>("Memeriksa...");
  const [isConnected, setIsConnected] = useState<boolean>(false);

  useEffect(() => {
    checkBackendConnection();
  }, []);

  const checkBackendConnection = async () => {
    try {
      const health = await api.checkHealth();
      setBackendStatus(`Backend Terhubung: ${health.status}`);
      setIsConnected(true);
    } catch (error) {
      setBackendStatus(`Backend Terputus`);
      setIsConnected(false);
    }
  };

  const handleStartSimulation = () => {
    // Navigate to simulation page or show simulation controls
    console.log("Starting simulation...");
  };

  const features = [
    {
      icon: <Train className="h-8 w-8 text-blue-600" />,
      title: "Simulasi Kereta Realistis",
      description:
        "Model fisika kereta api yang akurat dengan sistem propulsi, pengereman, dan dinamika yang realistis.",
    },
    {
      icon: <MapPin className="h-8 w-8 text-green-600" />,
      title: "Peta Rute Interaktif",
      description:
        "Jelajahi berbagai rute kereta api dengan visualisasi 3D yang mendetail dan navigasi yang intuitif.",
    },
    {
      icon: <Settings className="h-8 w-8 text-orange-600" />,
      title: "Kontrol Penuh",
      description:
        "Atur kecepatan, jadwal, dan parameter operasional kereta sesuai dengan kebutuhan simulasi.",
    },
    {
      icon: <BarChart3 className="h-8 w-8 text-purple-600" />,
      title: "Analisis Data",
      description:
        "Pantau performa, konsumsi energi, dan metrik operasional dengan dashboard analitik yang komprehensif.",
    },
    {
      icon: <Clock className="h-8 w-8 text-red-600" />,
      title: "Manajemen Jadwal",
      description:
        "Sistem penjadwalan otomatis dengan optimasi waktu tempuh dan efisiensi operasional.",
    },
    {
      icon: <Shield className="h-8 w-8 text-indigo-600" />,
      title: "Sistem Keamanan",
      description:
        "Simulasi sistem keamanan kereta api modern dengan protokol keselamatan yang terintegrasi.",
    },
  ];

  const stats = [
    {
      label: "Rute Tersedia",
      value: "15+",
      icon: <MapPin className="h-5 w-5" />,
    },
    { label: "Model Kereta", value: "8", icon: <Train className="h-5 w-5" /> },
    { label: "Stasiun", value: "45+", icon: <Users className="h-5 w-5" /> },
    {
      label: "Akurasi Fisika",
      value: "99.5%",
      icon: <Gauge className="h-5 w-5" />,
    },
  ];

  return (
    <SidebarProvider defaultOpen={false}>
      <div className="flex-1 flex flex-col min-h-screen">
        <div className="sticky top-0 z-10 bg-background/80 backdrop-blur-sm border-b">
          <div className="flex justify-between ml-30 p-4">
            <div className="flex items-center gap-4">
              <Badge
                variant={isConnected ? "default" : "destructive"}
                className="gap-1"
              >
                <Zap className="h-3 w-3" />
                {backendStatus}
              </Badge>
            </div>
            <div className="flex flex-row gap-4">
              <Link href={"/main"}>
                <Button>Mulai</Button>
              </Link>
              <ModeToggle />
            </div>
          </div>
        </div>

        {/* Hero Section */}
        <main className="relative overflow-hidden bg-gradient-to-br from-blue-50 via-indigo-50 to-purple-50 dark:from-blue-950/20 dark:via-indigo-950/20 dark:to-purple-950/20">
          <div className="absolute inset-0 bg-grid-black/[0.02] dark:bg-grid-white/[0.02]" />
          <div className="container mx-auto px-6 py-20 relative">
            <div className="text-center max-w-4xl mx-auto">
              <div className="inline-flex items-center gap-2 bg-blue-100 dark:bg-blue-900/30 px-4 py-2 rounded-full text-sm font-medium text-blue-600 dark:text-blue-400 mb-6">
                <Zap className="h-4 w-4" />
                Simulasi Kereta Api Terdepan
              </div>

              <h1 className="text-4xl md:text-6xl font-bold tracking-tight mb-6">
                Simulasi Kereta Api
                <span className="block text-transparent bg-clip-text bg-gradient-to-r from-blue-600 to-indigo-600">
                  Masa Depan
                </span>
              </h1>

              <p className="text-xl text-muted-foreground mb-8 leading-relaxed">
                Rasakan pengalaman mengemudi kereta api yang realistis dengan
                teknologi simulasi terdepan. Kendalikan berbagai jenis kereta,
                jelajahi rute yang menantang, dan pelajari sistem operasional
                kereta api modern dengan detail yang menakjubkan.
              </p>

              <div className="flex flex-col sm:flex-row gap-4 justify-center items-center">
                <Button
                  size="lg"
                  className="gap-2 px-8 py-6 text-lg"
                  onClick={handleStartSimulation}
                  disabled={!isConnected}
                >
                  <Play className="h-5 w-5" />
                  Mulai Simulasi
                </Button>

                <Button
                  variant="outline"
                  size="lg"
                  className="gap-2 px-8 py-6 text-lg"
                >
                  <BarChart3 className="h-5 w-5" />
                  Lihat Demo
                </Button>
              </div>
            </div>

            {/* Stats */}
            <div className="grid grid-cols-2 md:grid-cols-4 gap-6 max-w-3xl mx-auto mt-16">
              {stats.map((stat, index) => (
                <Card key={index} className="text-center">
                  <CardContent className="p-6">
                    <div className="flex justify-center mb-2 text-primary">
                      {stat.icon}
                    </div>
                    <div className="text-2xl font-bold mb-1">{stat.value}</div>
                    <div className="text-sm text-muted-foreground">
                      {stat.label}
                    </div>
                  </CardContent>
                </Card>
              ))}
            </div>
          </div>
        </main>

        {/* Features Section */}
        <div className="container mx-auto px-6 py-20">
          <div className="text-center mb-16">
            <h2 className="text-3xl md:text-4xl font-bold mb-4">
              Fitur Unggulan
            </h2>
            <p className="text-xl text-muted-foreground max-w-2xl mx-auto">
              Teknologi simulasi canggih yang memberikan pengalaman yang
              autentik dan edukatif
            </p>
          </div>

          <div className="grid md:grid-cols-2 lg:grid-cols-3 gap-8">
            {features.map((feature, index) => (
              <Card
                key={index}
                className="group hover:shadow-lg transition-all duration-300 border-0 shadow-md"
              >
                <CardHeader>
                  <div className="mb-4 group-hover:scale-110 transition-transform duration-300">
                    {feature.icon}
                  </div>
                  <CardTitle className="text-xl mb-2">
                    {feature.title}
                  </CardTitle>
                </CardHeader>
                <CardContent>
                  <CardDescription className="text-base leading-relaxed">
                    {feature.description}
                  </CardDescription>
                </CardContent>
              </Card>
            ))}
          </div>
        </div>

        {/* CTA Section */}
        <div className="bg-gradient-to-r from-blue-600 to-indigo-600 text-white">
          <div className="container mx-auto px-6 py-16 text-center">
            <h2 className="text-3xl md:text-4xl font-bold mb-4">
              Siap Memulai Perjalanan?
            </h2>
            <p className="text-xl mb-8 opacity-90 max-w-2xl mx-auto">
              Bergabunglah dengan ribuan pengguna yang telah merasakan
              pengalaman simulasi kereta api terbaik
            </p>
            <div className="flex flex-col sm:flex-row gap-4 justify-center">
              <Button
                size="lg"
                variant="secondary"
                className="gap-2 px-8 py-6 text-lg"
                onClick={handleStartSimulation}
                disabled={!isConnected}
              >
                <Play className="h-5 w-5" />
                Mulai Sekarang
              </Button>
              <Button
                size="lg"
                variant="outline"
                className="gap-2 px-8 py-6 text-lg border-white text-white hover:bg-white hover:text-blue-600"
                onClick={checkBackendConnection}
              >
                <Zap className="h-5 w-5" />
                Periksa Koneksi
              </Button>
            </div>
          </div>
        </div>

        {/* Footer */}
        <footer className="border-t bg-muted/50">
          <div className="container mx-auto px-6 py-8">
            <div className="flex flex-col md:flex-row justify-between items-center">
              <div className="flex items-center gap-2 text-lg font-semibold mb-4 md:mb-0">
                <Train className="h-6 w-6 text-blue-600" />
                Train Simulation App
              </div>
              <div className="text-sm text-muted-foreground">
                © 2024 Train Simulation. Dibuat dengan teknologi Qt & Electron.
              </div>
            </div>
          </div>
        </footer>
      </div>
    </SidebarProvider>
  );
}
