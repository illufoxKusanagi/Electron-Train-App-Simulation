"use client";
import { Calendar, Home, Ticket } from "lucide-react";

import {
  Sidebar,
  SidebarContent,
  SidebarFooter,
  SidebarGroup,
  SidebarGroupContent,
  SidebarHeader,
  SidebarMenu,
  SidebarMenuButton,
  useSidebar,
} from "@/components/ui/sidebar";
import { cn } from "@/lib/utils";
import Link from "next/link";

export function AppSidebar() {
  const { open } = useSidebar();

  const user = {
    name: "arief",
    email: "ariefsatria@gmail.com",
    avatar: "",
  };

  const items = [
    {
      title: "Dashboard",
      url: "/",
      icon: Home,
    },
    {
      title: "E-TIcketing",
      url: "#",
      icon: Ticket,
    },
    {
      title: "Kalender Kegiatan",
      url: "#",
      icon: Calendar,
    },
  ];
  return (
    <Sidebar variant="floating" collapsible="icon">
      <SidebarHeader
        className={cn(
          "overflow-hidden transition-all duration-500 ease-in-out",
          open ? "px-4 pt-4 block opacity-100" : "p-0 opacity-0 hidden"
        )}
      >
        <SidebarMenu>
          <SidebarMenuButton asChild className="hover:bg-accent/50 h-10">
            <p className="body-big-bold text-center text-primary">SATE-JIP</p>
          </SidebarMenuButton>
        </SidebarMenu>
      </SidebarHeader>

      <SidebarContent
        className={cn(
          "flex flex-col gap-4 transition-all duration-300",
          open ? "px-4 py-2" : "p-0 pt-4"
        )}
      >
        <SidebarMenu>
          <SidebarGroup>
            <SidebarGroupContent className="space-y-1">
              <SidebarMenu>
                {items.map((item) => (
                  <SidebarHeader key={item.title}>
                    <SidebarMenuButton asChild>
                      <Link href={item.url}>
                        <item.icon />
                        <span>{item.title}</span>
                      </Link>
                    </SidebarMenuButton>
                  </SidebarHeader>
                ))}
              </SidebarMenu>
            </SidebarGroupContent>
          </SidebarGroup>
        </SidebarMenu>
      </SidebarContent>
      <SidebarFooter
        className={cn(
          "absolute bottom-0 w-full border-t bg-background/95 backdrop-blur supports-[backdrop-filter]:bg-background/60",
          open ? "p-0" : "p-0"
        )}
      ></SidebarFooter>
    </Sidebar>
  );
}
